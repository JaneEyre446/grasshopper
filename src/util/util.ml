open Unix

module IntMap = Map.Make(struct
    type t = int
    let compare = compare
  end)


(** Utility functions on option types *)


let unopt = function
  | Some x -> x
  | None -> failwith "Util.unopt applied to None"

let safe_unopt default = function
  | Some x -> x
  | None -> default

let optmap f = function
  | Some x -> Some (f x)
  | None -> None


(** Utility functions on lists *)

(** generate a list of length [n] using generator [f] *)
let generate_list (f : int -> 'a) (n : int) : 'a list = 
  let rec mk_tl n acc = 
    if n <= 0 then acc 
    else mk_tl (n - 1) (f n :: acc) 
  in mk_tl n []


(** Composition of [List.map] and [List.filter] *)
let filter_map p f xs =
  List.fold_right (fun x ys -> if p x then f x :: ys else ys) xs []

let flat_map f ls = List.flatten (List.map f ls)

let rec partial_map f = function
  | [] -> []
  | x :: xs -> 
      match f x with 
      |	Some y -> y :: partial_map f xs
      |	None -> partial_map f xs

(** Tail-recursive concatenation of lists *)
let rev_concat lists = List.fold_left (List.fold_left (fun acc f -> f :: acc)) [] lists


(** Boolean operators on predicates *)

let (~~) f x = not (f x)

let (&&&) f g x = f x && g x

let (|||) f g x = f x || g x


(* the following is stripped from module BatSubstring in OCaml Batteries included *)

type t = string * int * int (* string, offset, length *)

let empty () = "", 0, 0

let to_string (s,o,l) = String.sub s o l

let of_string s = s, 0, String.length s

let splitl p (str, off, len) = 
  let i = ref 0 in
  while !i < len && p str.[off+ !i] do incr i; done;
  (str, off+ !i, len- !i), (str, off, !i)

let split_on_char c (str, off, len) = 
  let rec loop acc last_pos pos =
    if pos = -1 then
      (str, 0, last_pos) :: acc
    else
      if str.[pos] = c then
        let pos1 = pos + 1 in
        let sub_str = str,pos1,(last_pos - pos1) in
        loop (sub_str :: acc) pos (pos - 1)
      else loop acc last_pos (pos - 1)
  in
  loop [] len (len - 1)

let split_on_comma str = split_on_char ',' str;;

let measured_time = ref 0.
let measured_calls = ref 0

(** measure accumulated execution time and number of calls to a particular function *)
let measure fn arg =
  let start_time = 
    let ptime = Unix.times () in
    ptime.tms_utime
  in
  try
    let res = fn arg in
    let end_time = 
      let ptime = Unix.times () in
      ptime.Unix.tms_utime
    in
    measured_time := !measured_time +. (end_time -. start_time);
    incr measured_calls;
    res
  with e ->
    let end_time = 
      let ptime = Unix.times () in
      ptime.Unix.tms_utime
    in
    measured_time := !measured_time +. (end_time -. start_time);
    incr measured_calls;
    raise e

let measures = Hashtbl.create 10

let measure_call (id: string) fn arg =
  let get_time () = 
    let ptime = Unix.times () in
    ptime.tms_utime
  in
  let (calls, time) =
    if Hashtbl.mem measures id
    then Hashtbl.find measures id
    else (0, 0.)
  in
  let start_time = get_time () in
  try
    let res = fn arg in
    let end_time = get_time () in
    Hashtbl.replace measures id (calls + 1, time +. end_time -. start_time);
    res
  with e ->
    let end_time = get_time () in
    Hashtbl.replace measures id (calls + 1, time +. end_time -. start_time);
    raise e

let print_measures () =
  Hashtbl.iter
    (fun id (calls, time) ->
      print_endline (id ^ ": " ^ (string_of_int calls) ^ " call(s), " ^ (string_of_float time) ^ " s")
    )
    measures

let read_file file =
  let chan = open_in file in
  let rec read acc =
    try
      read (input_line chan :: acc)
    with End_of_file ->
      begin
        close_in chan;
        List.rev acc
      end
  in
    String.concat "\n" (read [])
