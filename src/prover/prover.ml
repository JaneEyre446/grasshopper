open Grass
open GrassUtil
open Util
open Axioms

let inst_num = ref 0

let dump_model session f =
  if !Config.model_file <> "" then begin
    let gts = ground_terms ~include_atoms:true f in
    let model = Opt.get (SmtLibSolver.get_model session) in
    let model_chan = open_out !Config.model_file in
    if Str.string_match (Str.regexp ".*\\.html$") !Config.model_file 0 then
      Model.output_html model_chan (Model.complete model) gts
    else
      Model.output_graph model_chan (Model.complete model) gts;
    close_out model_chan;
  end

let dump_core session =
  if !Config.unsat_cores then
    begin
      let core_name = session.SmtLibSolver.log_file_name ^ ".core" in
      (*repeat in a fixed point in order to get a smaller core*)
      let rec minimize core =
        Debug.info (fun () -> "minimizing core " ^ (string_of_int (List.length core)) ^ "\n");
        let s = SmtLibSolver.start core_name session.SmtLibSolver.sat_means in
        let signature = overloaded_sign (mk_and core) in
        let s = SmtLibSolver.declare s signature in
        SmtLibSolver.assert_forms s core;
        let core2 = Opt.get (SmtLibSolver.get_unsat_core s) in
        SmtLibSolver.quit s;
        if List.length core2 < List.length core
        then minimize core2
        else core
      in
      let core = Opt.get (SmtLibSolver.get_unsat_core session) in
      let core = minimize core in
      let config = !Config.dump_smt_queries in
      Config.dump_smt_queries := true;
      let s = SmtLibSolver.start core_name session.SmtLibSolver.sat_means in
      let signature = overloaded_sign (mk_and core) in
      let s = SmtLibSolver.declare s signature in
      SmtLibSolver.assert_forms s core;
      SmtLibSolver.quit s;
      Config.dump_smt_queries := config
    end

let print_query name sat_means f =
  let f_inst = Reduction.reduce f in
  let f_inst =
    if !Config.named_assertions then
      let f_inst = List.rev_map unique_names f_inst in
      let f_inst = List.rev_map name_unnamed f_inst in
      f_inst
    else f_inst
  in
  let signature = overloaded_sign (mk_and f_inst) in
  let session = SmtLibSolver.start name sat_means in
  Debug.debug (fun () -> "Sending to prover...\n");
  let session = SmtLibSolver.declare session signature in
  SmtLibSolver.assert_forms session f_inst;
  session, f_inst


let start_session name sat_means f = 
  let session, f_inst = print_query name sat_means f in
  let prove session =
    let result = SmtLibSolver.is_sat session in
    Debug.debug (fun () -> "prover done\n");
    (result, session)
  in
  (*Util.measure_call "prove" prove session*)
  let result, session = prove session in
  result, session, mk_and f_inst

let check_sat ?(session_name="form") ?(sat_means="sat") f =
  let result, session, f_inst = start_session session_name sat_means f in
  (match result with
  | Some true -> dump_model session f_inst
  | Some false -> dump_core session
  | _ -> ());
  SmtLibSolver.quit session;
  result

let get_model ?(session_name="form") ?(sat_means="sat") f =
  let result, session, f_inst = start_session session_name sat_means f in
  let model = 
    match result with
    | Some true | None ->
        dump_model session f_inst;
        SmtLibSolver.get_model session
    | Some false -> 
        dump_core session;
        None
  in
  SmtLibSolver.quit session;
  Util.Opt.map Model.complete model
