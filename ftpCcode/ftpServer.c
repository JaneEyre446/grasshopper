/*
 * Includes
 */
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <netinet/in.h>

/*
 * Preloaded Code
 */

typedef struct {
  int length;
  int arr[];
} SPLArray_int;

SPLArray_int* newSPLArray_int(int size) {
  SPLArray_int* a = (SPLArray_int*)malloc(sizeof(SPLArray_int) + size * sizeof(int));
  assert(a != NULL);
  a->length = size;
  return a;
}

typedef struct {
  int length;
  bool arr[];
} SPLArray_bool;

SPLArray_bool* newSPLArray_bool(int size) {
  SPLArray_bool* a = (SPLArray_bool*)malloc(sizeof(SPLArray_bool) + size * sizeof(bool));
  assert(a != NULL);
  a->length = size;
  return a;
}

typedef struct {
  int length;
  char arr[];
} SPLArray_char;

SPLArray_char* newSPLArray_char(int size) {
  SPLArray_char* a = (SPLArray_char*)malloc(sizeof(SPLArray_char) + size * sizeof(char));
  assert(a != NULL);
  a->length = size;
  return a;
}

typedef struct {
  int length;
  void* arr[];
} SPLArray_generic;

SPLArray_generic* newSPLArray_generic(int size) {
  SPLArray_generic* a = (SPLArray_generic*)malloc(sizeof(SPLArray_generic) + size * sizeof(void*));
  assert(a != NULL);
  a->length = size;
  return a;
}

/*
 * Structs
 */
struct SocketAddressIP4;
struct SocketAddressIP6;

typedef struct SocketAddressIP4 {
  int sin4_addr;
  int sin4_port;
} SocketAddressIP4;

typedef struct SocketAddressIP6 {
  SPLArray_char* sin6_addr;
  int sin6_flowinfo;
  int sin6_port;
  int sin6_scope_id;
} SocketAddressIP6;

/*
 * Procedures
 */
int Main (SPLArray_char* args);
int accept4 (int fd, struct SocketAddressIP4* address);
int accept6 (int fd_1, struct SocketAddressIP6* address_1);
int accept_incoming_file (int dataFd, SPLArray_char* filename);
int atoiFrom (SPLArray_char* str, int startIdx);
int atoiG (SPLArray_char* str_1);
bool bind4 (int fd_2, struct SocketAddressIP4* address_2);
bool bind6 (int fd_3, struct SocketAddressIP6* address_3);
SPLArray_char* concat (SPLArray_char* str1, SPLArray_char* str2);
bool connect4 (int fd_4, struct SocketAddressIP4* address_4);
bool connect6 (int fd_5, struct SocketAddressIP6* address_5);
int connectMeCommand (SPLArray_char* port);
SPLArray_char* copy_byte_slice (SPLArray_char* a, int start, int end);
int create_socket (int inet_type, int socket_type, int protocol);
bool equals (SPLArray_char* first, SPLArray_char* second);
int fileSize (SPLArray_char* pathname);
int gclose (int fd_7);
struct SocketAddressIP4* get_address4 (SPLArray_char* node, SPLArray_char* service);
struct SocketAddressIP6* get_address6 (SPLArray_char* node_1, SPLArray_char* service_1);
int ggets (SPLArray_char* buffer_1);
bool glisten (int fd_8, int backlog);
int gopen (SPLArray_char* pathname_1, int flags);
int gputs (SPLArray_char* buffer_2);
int gread (int fd_10, SPLArray_char* buffer_3);
int greadOffset (int fd_11, SPLArray_char* buffer_4, int offset);
int gwrite (int fd_12, SPLArray_char* buffer_5);
int gwrite2 (int fd_13, SPLArray_char* buffer_6, int size_1);
bool handleAuth (int cmdFd_1);
bool is_retr (SPLArray_char* cmd);
bool is_size (SPLArray_char* cmd_1);
bool is_stor (SPLArray_char* cmd_2);
SPLArray_char* process_string (SPLArray_char* thing);
int recvDataConnection (int cmdFd_2);
bool retr_help (int cmdFd_3, int dataFd_1, SPLArray_char* filename_1);
bool send_outgoing_file (int dataFd_2, SPLArray_char* filename_2);
int server ();
bool size_help (int cmdFd_5, SPLArray_char* filename_4);
bool store_help (int cmdFd_6, int dataFd_4, SPLArray_char* filename_5);
int strcat (SPLArray_char* str1_1, SPLArray_char* str2_1);
int strcmp (SPLArray_char* s1, SPLArray_char* s2);
SPLArray_char* strconcat (SPLArray_char* str1_2, SPLArray_char* str2_2);
SPLArray_char* strdup (SPLArray_char* str_2);
int strlen (SPLArray_char* str_3);
int tcp_recv (int fd_15, SPLArray_char* msg);
int tcp_send (int fd_16, SPLArray_char* msg_1, int len);
int udp_recv4 (int fd_17, SPLArray_char* msg_2, struct SocketAddressIP4* from);
int udp_recv6 (int fd_18, SPLArray_char* msg_3, struct SocketAddressIP6* from_1);
int udp_send4 (int fd_19, SPLArray_char* msg_4, int len_1, struct SocketAddressIP4* address_8);
int udp_send6 (int fd_20, SPLArray_char* msg_5, int len_2, struct SocketAddressIP6* address_9);

int Main (SPLArray_char* args) {
  int res;
  res = server();
  return res;
}

int accept_incoming_file (int dataFd, SPLArray_char* filename) {
  int res_1;
  int written;
  SPLArray_char* tmp;
  int recv;
  int fileFd;
  int closed;
  SPLArray_char* buffer;
  
  tmp = newSPLArray_char( 65535);
  buffer = tmp;
  recv = tcp_recv(dataFd, buffer);
  if ((recv < 0)) {
    free(buffer);
    
    return (-1);
  }
  fileFd = gopen(filename, (O_CREAT | O_TRUNC));
  if ((fileFd < 0)) {
    free(buffer);
    
    return (-1);
  }
  written = gwrite(fileFd, buffer);
  free(buffer);
  
  closed = gclose(fileFd);
  if (((written < 0) || (closed < 0))) {
    return (-1);
  }
  return 1;
}

int atoiFrom (SPLArray_char* str, int startIdx) {
  int res_2;
  bool isPositive;
  int i;
  bool foundStart;
  bool foundEnd;
  int digit;
  
  res_2 = 0;
  i = startIdx;
  if ((i > (str->length))) {
    i = (str->length);
  }
  foundStart = false;
  foundEnd = false;
  isPositive = true;
  while (true) {
    if (!(((i < (str->length)) && (!foundStart)))) {
      break;
    }
    if ((((((((str->arr[i]) == ((char) 9)) || ((str->arr[i]) == ((char) 10))) || ((str->arr[i]) == ((char) 11))) || ((str->arr[i]) == ((char) 12))) || ((str->arr[i]) == ((char) 13))) || ((str->arr[i]) == ((char) 32)))) {
      i = (i + 1);
    } else {
      foundStart = true;
    }
  }
  if ((i < (str->length))) {
    if (((str->arr[i]) == ((char) 45))) {
      isPositive = false;
      i = (i + 1);
    }
  }
  while (true) {
    if (!(((i < (str->length)) && (!foundEnd)))) {
      break;
    }
    if ((((str->arr[i]) >= ((char) 48)) && ((str->arr[i]) <= ((char) 57)))) {
      digit = ((int) ((str->arr[i]) - ((char) 48)));
      res_2 = (res_2 * 10);
      res_2 = (res_2 + digit);
      i = (i + 1);
    } else {
      foundEnd = true;
    }
  }
  if ((!isPositive)) {
    res_2 = ((-1) * res_2);
  }
  return res_2;
}

int atoiG (SPLArray_char* str_1) {
  int res_3;
  res_3 = atoiFrom(str_1, 0);
  return res_3;
  return res_3;
}

SPLArray_char* concat (SPLArray_char* str1, SPLArray_char* str2) {
  SPLArray_char* res_4;
  SPLArray_char* tmp_1;
  int i_2;
  SPLArray_char* copy;
  
  
  tmp_1 = newSPLArray_char( ((str1->length) + (str2->length)));
  copy = tmp_1;
  i_2 = 0;
  while (true) {
    if (!((i_2 < (str1->length)))) {
      break;
    }
    (copy->arr[i_2]) = (str1->arr[i_2]);
    i_2 = (i_2 + 1);
  }
  while (true) {
    if (!((i_2 < ((str1->length) + (str2->length))))) {
      break;
    }
    (copy->arr[i_2]) = (str2->arr[(i_2 - (str1->length))]);
    i_2 = (i_2 + 1);
  }
  return copy;
}

int connectMeCommand (SPLArray_char* port) {
  int res_5;
  bool listening;
  int connFd;
  int cmdFd;
  struct SocketAddressIP4* cmdAddr;
  int closed_1;
  bool bound;
  
  cmdAddr = get_address4(NULL, port);
  free(port);
  
  if ((cmdAddr == NULL)) {
    return (-1);
  }
  cmdFd = create_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((cmdFd == (-1))) {
    free(cmdAddr);
    
    return (-1);
  }
  bound = bind4(cmdFd, cmdAddr);
  if ((!bound)) {
    free(cmdAddr);
    
    return (-1);
  }
  listening = glisten(cmdFd, 10);
  if ((!listening)) {
    free(cmdAddr);
    
    return (-1);
  }
  connFd = accept4(cmdFd, cmdAddr);
  free(cmdAddr);
  
  closed_1 = gclose(cmdFd);
  return connFd;
}

SPLArray_char* copy_byte_slice (SPLArray_char* a, int start, int end) {
  SPLArray_char* b;
  SPLArray_char* tmp_2;
  int i_5;
  int finalLength;
  
  finalLength = (end - start);
  tmp_2 = newSPLArray_char( finalLength);
  b = tmp_2;
  i_5 = 0;
  while (true) {
    if (!((i_5 < finalLength))) {
      break;
    }
    (b->arr[i_5]) = (a->arr[(i_5 + start)]);
    i_5 = (i_5 + 1);
  }
  return b;
}

bool equals (SPLArray_char* first, SPLArray_char* second) {
  bool res_6;
  int i_7;
  
  if ((!((first->length) == (second->length)))) {
    return false;
  }
  i_7 = 0;
  while (true) {
    if (!(((i_7 < (first->length)) && ((first->arr[i_7]) == (second->arr[i_7]))))) {
      break;
    }
    i_7 = (i_7 + 1);
  }
  if ((i_7 >= (first->length))) {
    return true;
  } else {
    return false;
  }
  return res_6;
}

bool handleAuth (int cmdFd_1) {
  bool success_5;
  SPLArray_char* userName;
  SPLArray_char* tmp_8;
  int tmp_7;
  SPLArray_char* tmp_6;
  SPLArray_char* tmp_5;
  SPLArray_char* tmp_4;
  SPLArray_char* tmp_3;
  SPLArray_char* sentPassword;
  int sent_2;
  int sent_1;
  int sent;
  SPLArray_char* response;
  int recvpass;
  int recvUser;
  SPLArray_char* pass;
  bool isOkay;
  
  tmp_3 = newSPLArray_char( 12);
  userName = tmp_3;
  recvUser = tcp_recv(cmdFd_1, userName);
  free(userName);
  
  tmp_4 = newSPLArray_char( 4);
  response = tmp_4;
  (response->arr[0]) = ((char) 51);
  (response->arr[1]) = ((char) 51);
  (response->arr[2]) = ((char) 49);
  (response->arr[3]) = ((char) 0);
  sent = tcp_send(cmdFd_1, response, 4);
  free(response);
  
  tmp_5 = newSPLArray_char( 15);
  sentPassword = tmp_5;
  recvpass = tcp_recv(cmdFd_1, sentPassword);
  tmp_6 = newSPLArray_char( 15);
  pass = tmp_6;
  (pass->arr[0]) = ((char) 80);
  (pass->arr[1]) = ((char) 65);
  (pass->arr[2]) = ((char) 83);
  (pass->arr[3]) = ((char) 83);
  (pass->arr[4]) = ((char) 32);
  (pass->arr[5]) = ((char) 97);
  (pass->arr[6]) = ((char) 110);
  (pass->arr[7]) = ((char) 111);
  (pass->arr[8]) = ((char) 110);
  (pass->arr[9]) = ((char) 121);
  (pass->arr[10]) = ((char) 109);
  (pass->arr[11]) = ((char) 111);
  (pass->arr[12]) = ((char) 117);
  (pass->arr[13]) = ((char) 115);
  (pass->arr[14]) = ((char) 0);
  isOkay = false;
  tmp_7 = strcmp(pass, sentPassword);
  if ((tmp_7 == 0)) {
    isOkay = true;
  }
  free(sentPassword);
  
  free(pass);
  
  tmp_8 = newSPLArray_char( 4);
  response = tmp_8;
  if (isOkay) {
    (response->arr[0]) = ((char) 50);
    (response->arr[1]) = ((char) 51);
    (response->arr[2]) = ((char) 48);
    (response->arr[3]) = ((char) 0);
    sent_1 = tcp_send(cmdFd_1, response, 4);
    free(response);
    
    return true;
  } else {
    (response->arr[0]) = ((char) 52);
    (response->arr[1]) = ((char) 51);
    (response->arr[2]) = ((char) 48);
    (response->arr[3]) = ((char) 0);
    sent_2 = tcp_send(cmdFd_1, response, 4);
    free(response);
    
    return false;
  }
  return success_5;
}

bool is_retr (SPLArray_char* cmd) {
  bool is;
  int tmp_10;
  SPLArray_char* tmp_9;
  SPLArray_char* retr;
  
  tmp_9 = newSPLArray_char( 5);
  retr = tmp_9;
  (retr->arr[0]) = ((char) 82);
  (retr->arr[1]) = ((char) 69);
  (retr->arr[2]) = ((char) 84);
  (retr->arr[3]) = ((char) 82);
  (retr->arr[4]) = ((char) 0);
  tmp_10 = strcmp(cmd, retr);
  if ((tmp_10 == 0)) {
    free(retr);
    
    return true;
  } else {
    free(retr);
    
    return false;
  }
  return is;
}

bool is_size (SPLArray_char* cmd_1) {
  bool is_1;
  int tmp_12;
  SPLArray_char* tmp_11;
  SPLArray_char* size_2;
  
  tmp_11 = newSPLArray_char( 5);
  size_2 = tmp_11;
  (size_2->arr[0]) = ((char) 83);
  (size_2->arr[1]) = ((char) 73);
  (size_2->arr[2]) = ((char) 90);
  (size_2->arr[3]) = ((char) 69);
  (size_2->arr[4]) = ((char) 0);
  tmp_12 = strcmp(cmd_1, size_2);
  if ((tmp_12 == 0)) {
    free(size_2);
    
    return true;
  } else {
    free(size_2);
    
    return false;
  }
  return is_1;
}

bool is_stor (SPLArray_char* cmd_2) {
  bool is_2;
  int tmp_14;
  SPLArray_char* tmp_13;
  SPLArray_char* stor;
  
  tmp_13 = newSPLArray_char( 5);
  stor = tmp_13;
  (stor->arr[0]) = ((char) 83);
  (stor->arr[1]) = ((char) 84);
  (stor->arr[2]) = ((char) 79);
  (stor->arr[3]) = ((char) 82);
  (stor->arr[4]) = ((char) 0);
  tmp_14 = strcmp(cmd_2, stor);
  if ((tmp_14 == 0)) {
    free(stor);
    
    return true;
  } else {
    free(stor);
    
    return false;
  }
  return is_2;
}

SPLArray_char* process_string (SPLArray_char* thing) {
  SPLArray_char* out;
  SPLArray_char* tmp_15;
  int copied;
  
  tmp_15 = newSPLArray_char( ((thing->length) + 1));
  out = tmp_15;
  (out->arr[0]) = ((char) 0);
  copied = strcat(thing, out);
  free(thing);
  
  (out->arr[((out->length) - 1)]) = ((char) 0);
  return out;
}

int recvDataConnection (int cmdFd_2) {
  int res_7;
  bool tmp_17;
  SPLArray_char* tmp_16;
  int response_1;
  SPLArray_char* resp;
  SPLArray_char* portArray;
  int fd_14;
  int closing;
  struct SocketAddressIP4* addr;
  
  tmp_16 = newSPLArray_char( 10);
  resp = tmp_16;
  response_1 = tcp_recv(cmdFd_2, resp);
  fd_14 = create_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((fd_14 == (-1))) {
    free(resp);
    
    return (-1);
  }
  portArray = copy_byte_slice(resp, 5, 10);
  free(resp);
  
  addr = get_address4(NULL, portArray);
  free(portArray);
  
  if ((addr == NULL)) {
    return (-1);
  }
  tmp_17 = connect4(fd_14, addr);
  if (tmp_17) {
    free(addr);
    
    return fd_14;
  } else {
    free(addr);
    
    closing = gclose(fd_14);
    return (-1);
  }
  return res_7;
}

bool retr_help (int cmdFd_3, int dataFd_1, SPLArray_char* filename_1) {
  bool fail;
  SPLArray_char* tmp_20;
  SPLArray_char* tmp_19;
  SPLArray_char* tmp_18;
  int sent_3;
  SPLArray_char* ok;
  SPLArray_char* notOk;
  SPLArray_char* goodPacket;
  bool done;
  
  tmp_18 = newSPLArray_char( 4);
  ok = tmp_18;
  (ok->arr[0]) = ((char) 49);
  (ok->arr[1]) = ((char) 53);
  (ok->arr[2]) = ((char) 48);
  (ok->arr[3]) = ((char) 0);
  sent_3 = tcp_send(cmdFd_3, ok, 4);
  free(ok);
  
  done = send_outgoing_file(dataFd_1, filename_1);
  if ((!done)) {
    tmp_19 = newSPLArray_char( 4);
    notOk = tmp_19;
    (notOk->arr[0]) = ((char) 53);
    (notOk->arr[1]) = ((char) 53);
    (notOk->arr[2]) = ((char) 48);
    (notOk->arr[3]) = ((char) 0);
    sent_3 = tcp_send(cmdFd_3, notOk, 4);
    free(notOk);
    
    return true;
  }
  tmp_20 = newSPLArray_char( 4);
  goodPacket = tmp_20;
  (goodPacket->arr[0]) = ((char) 50);
  (goodPacket->arr[1]) = ((char) 53);
  (goodPacket->arr[2]) = ((char) 48);
  (goodPacket->arr[3]) = ((char) 0);
  sent_3 = tcp_send(cmdFd_3, goodPacket, 4);
  free(goodPacket);
  
  return true;
}

bool send_outgoing_file (int dataFd_2, SPLArray_char* filename_2) {
  bool res_8;
  SPLArray_char* tmp_21;
  int sent_4;
  int read;
  bool flag;
  int fileS;
  int fileFd_1;
  int closed_2;
  SPLArray_char* buffer_7;
  
  fileFd_1 = gopen(filename_2, O_CREAT);
  flag = false;
  if ((fileFd_1 < 0)) {
    flag = true;
  }
  fileS = fileSize(filename_2);
  if (((fileS < 0) || (fileS > 65535))) {
    fileS = 0;
    flag = true;
  }
  tmp_21 = newSPLArray_char( fileS);
  buffer_7 = tmp_21;
  if ((!flag)) {
    read = gread(fileFd_1, buffer_7);
    closed_2 = gclose(fileFd_1);
    if (((read < 0) || (closed_2 < 0))) {
      flag = true;
    }
  }
  if ((!flag)) {
    sent_4 = tcp_send(dataFd_2, buffer_7, fileS);
    if ((sent_4 < 0)) {
      flag = true;
    }
  }
  free(buffer_7);
  
  if (flag) {
    return false;
  } else {
    return true;
  }
  return res_8;
}

int server () {
  int res_9;
  SPLArray_char* typeCom;
  int tmp_30;
  SPLArray_char* tmp_29;
  SPLArray_char* tmp_28;
  SPLArray_char* tmp_27;
  bool tmp_26;
  bool tmp_25;
  bool tmp_24;
  SPLArray_char* tmp_23;
  SPLArray_char* tmp_22;
  bool temp_2;
  bool temp_1;
  bool temp;
  int sent_5;
  SPLArray_char* request;
  int recv_1;
  int recd;
  SPLArray_char* quitBuff;
  SPLArray_char* quit;
  SPLArray_char* port_1;
  bool iQuit;
  SPLArray_char* final;
  SPLArray_char* filename_3;
  int dataFd_3;
  int cmdFd_4;
  int closed_4;
  int closed_3;
  SPLArray_char* badPacket;
  bool authenticated;
  
  tmp_22 = newSPLArray_char( 5);
  port_1 = tmp_22;
  (port_1->arr[0]) = ((char) 52);
  (port_1->arr[1]) = ((char) 52);
  (port_1->arr[2]) = ((char) 52);
  (port_1->arr[3]) = ((char) 52);
  (port_1->arr[4]) = ((char) 0);
  cmdFd_4 = connectMeCommand(port_1);
  if ((cmdFd_4 <= (-1))) {
    return (-1);
  }
  dataFd_3 = recvDataConnection(cmdFd_4);
  if ((dataFd_3 <= (-1))) {
    closed_3 = gclose(cmdFd_4);
    return (-1);
  }
  authenticated = handleAuth(cmdFd_4);
  if ((!authenticated)) {
    return (-1);
  }
  iQuit = false;
  while (true) {
    if (!((!iQuit))) {
      break;
    }
    tmp_23 = newSPLArray_char( 100);
    request = tmp_23;
    recd = tcp_recv(cmdFd_4, request);
    typeCom = copy_byte_slice(request, 0, 4);
    final = process_string(typeCom);
    filename_3 = copy_byte_slice(request, 5, ((request->length) - 1));
    free(request);
    
    tmp_24 = is_stor(final);
    if (tmp_24) {
      temp = store_help(cmdFd_4, dataFd_3, filename_3);
      if (temp) {
        free(filename_3);
        
        free(final);
        
      }
      iQuit = temp;
    } else {
      tmp_25 = is_size(final);
      if (tmp_25) {
        temp_1 = size_help(cmdFd_4, filename_3);
        if (temp_1) {
          free(filename_3);
          
          free(final);
          
        }
        iQuit = temp_1;
      } else {
        tmp_26 = is_retr(final);
        if (tmp_26) {
          temp_2 = retr_help(cmdFd_4, dataFd_3, filename_3);
          if (temp_2) {
            free(filename_3);
            
            free(final);
            
          }
          iQuit = temp_2;
        } else {
          tmp_27 = newSPLArray_char( 4);
          badPacket = tmp_27;
          (badPacket->arr[0]) = ((char) 53);
          (badPacket->arr[1]) = ((char) 48);
          (badPacket->arr[2]) = ((char) 48);
          (badPacket->arr[3]) = ((char) 0);
          sent_5 = tcp_send(cmdFd_4, badPacket, 4);
          free(badPacket);
          
          iQuit = true;
        }
      }
    }
    free(filename_3);
    
    free(final);
    
  }
  tmp_28 = newSPLArray_char( 5);
  quitBuff = tmp_28;
  recv_1 = tcp_recv(cmdFd_4, quitBuff);
  tmp_29 = newSPLArray_char( 5);
  quit = tmp_29;
  (quit->arr[0]) = ((char) 81);
  (quit->arr[1]) = ((char) 85);
  (quit->arr[2]) = ((char) 73);
  (quit->arr[3]) = ((char) 84);
  (quit->arr[4]) = ((char) 0);
  tmp_30 = strcmp(quitBuff, quit);
  if ((tmp_30 == 0)) {
    free(quit);
    
    free(quitBuff);
    
    closed_4 = gclose(cmdFd_4);
    closed_4 = gclose(dataFd_3);
    return 0;
  } else {
    free(quit);
    
    free(quitBuff);
    
    return (-1);
  }
  return res_9;
}

bool size_help (int cmdFd_5, SPLArray_char* filename_4) {
  bool fail_1;
  SPLArray_char* tmp_33;
  SPLArray_char* tmp_32;
  SPLArray_char* tmp_31;
  SPLArray_char* sizePacket;
  int sizeF;
  int sent_7;
  int sent_6;
  SPLArray_char* goodPacket_1;
  int finished;
  SPLArray_char* badPacket_1;
  
  sizeF = fileSize(filename_4);
  if ((sizeF < 0)) {
    tmp_31 = newSPLArray_char( 4);
    badPacket_1 = tmp_31;
    (badPacket_1->arr[0]) = ((char) 53);
    (badPacket_1->arr[1]) = ((char) 53);
    (badPacket_1->arr[2]) = ((char) 48);
    (badPacket_1->arr[3]) = ((char) 0);
    sent_6 = tcp_send(cmdFd_5, badPacket_1, 4);
    free(badPacket_1);
    
    return true;
  }
  tmp_32 = newSPLArray_char( 1);
  sizePacket = tmp_32;
  (sizePacket->arr[0]) = ((char) sizeF);
  tmp_33 = newSPLArray_char( 6);
  goodPacket_1 = tmp_33;
  (goodPacket_1->arr[0]) = ((char) 50);
  (goodPacket_1->arr[1]) = ((char) 49);
  (goodPacket_1->arr[2]) = ((char) 51);
  (goodPacket_1->arr[3]) = ((char) 32);
  (goodPacket_1->arr[4]) = ((char) 0);
  finished = strcat(sizePacket, goodPacket_1);
  sent_7 = tcp_send(cmdFd_5, goodPacket_1, 6);
  free(sizePacket);
  
  free(goodPacket_1);
  
  return false;
}

bool store_help (int cmdFd_6, int dataFd_4, SPLArray_char* filename_5) {
  bool fail_2;
  SPLArray_char* tmp_36;
  SPLArray_char* tmp_35;
  SPLArray_char* tmp_34;
  int stored;
  int sent_8;
  SPLArray_char* ok_1;
  SPLArray_char* notOk_1;
  SPLArray_char* goodPacket_2;
  
  tmp_34 = newSPLArray_char( 4);
  ok_1 = tmp_34;
  (ok_1->arr[0]) = ((char) 49);
  (ok_1->arr[1]) = ((char) 53);
  (ok_1->arr[2]) = ((char) 48);
  (ok_1->arr[3]) = ((char) 0);
  sent_8 = tcp_send(cmdFd_6, ok_1, 4);
  free(ok_1);
  
  stored = accept_incoming_file(dataFd_4, filename_5);
  if ((stored < 0)) {
    tmp_35 = newSPLArray_char( 4);
    notOk_1 = tmp_35;
    (notOk_1->arr[0]) = ((char) 53);
    (notOk_1->arr[1]) = ((char) 53);
    (notOk_1->arr[2]) = ((char) 48);
    (notOk_1->arr[3]) = ((char) 0);
    sent_8 = tcp_send(cmdFd_6, notOk_1, 4);
    free(notOk_1);
    
    return true;
  }
  tmp_36 = newSPLArray_char( 4);
  goodPacket_2 = tmp_36;
  (goodPacket_2->arr[0]) = ((char) 50);
  (goodPacket_2->arr[1]) = ((char) 53);
  (goodPacket_2->arr[2]) = ((char) 48);
  (goodPacket_2->arr[3]) = ((char) 0);
  sent_8 = tcp_send(cmdFd_6, goodPacket_2, 4);
  free(goodPacket_2);
  
  return false;
}

int strcat (SPLArray_char* str1_1, SPLArray_char* str2_1) {
  int res_10;
  int l2;
  int l1;
  int i_13;
  int copy_size;
  
  l1 = strlen(str1_1);
  l2 = strlen(str2_1);
  copy_size = ((str2_1->length) - l2);
  if ((copy_size > l1)) {
    copy_size = l1;
  }
  i_13 = 0;
  while (true) {
    if (!((i_13 < copy_size))) {
      break;
    }
    (str2_1->arr[(i_13 + l2)]) = (str1_1->arr[i_13]);
    i_13 = (i_13 + 1);
  }
  if (((l2 + copy_size) < (str2_1->length))) {
    (str2_1->arr[(l2 + copy_size)]) = ((char) 0);
  }
  return copy_size;
}

int strcmp (SPLArray_char* s1, SPLArray_char* s2) {
  int res_11;
  int i_15;
  
  i_15 = 0;
  while (true) {
    if (!((((i_15 < (s1->length)) && (i_15 < (s2->length))) && ((s1->arr[i_15]) == (s2->arr[i_15]))))) {
      break;
    }
    i_15 = (i_15 + 1);
  }
  if (((i_15 >= (s1->length)) && (i_15 >= (s2->length)))) {
    return 0;
  } else {
    if ((i_15 >= (s1->length))) {
      return (-1);
    } else {
      if ((i_15 >= (s2->length))) {
        return 1;
      } else {
        if (((s1->arr[i_15]) < (s2->arr[i_15]))) {
          return (-1);
        } else {
          return 1;
        }
      }
    }
  }
  return res_11;
}

SPLArray_char* strconcat (SPLArray_char* str1_2, SPLArray_char* str2_2) {
  SPLArray_char* res_12;
  SPLArray_char* tmp_37;
  int l2_1;
  int l1_1;
  int i_16;
  SPLArray_char* copy_1;
  
  l1_1 = strlen(str1_2);
  l2_1 = strlen(str2_2);
  
  tmp_37 = newSPLArray_char( (l1_1 + l2_1));
  copy_1 = tmp_37;
  i_16 = 0;
  while (true) {
    if (!((i_16 < l1_1))) {
      break;
    }
    (copy_1->arr[i_16]) = (str1_2->arr[i_16]);
    i_16 = (i_16 + 1);
  }
  while (true) {
    if (!((i_16 < (l1_1 + l2_1)))) {
      break;
    }
    (copy_1->arr[i_16]) = (str2_2->arr[(i_16 - l1_1)]);
    i_16 = (i_16 + 1);
  }
  return copy_1;
}

SPLArray_char* strdup (SPLArray_char* str_2) {
  SPLArray_char* res_13;
  SPLArray_char* tmp_38;
  int i_18;
  SPLArray_char* copy_2;
  
  tmp_38 = newSPLArray_char( (str_2->length));
  copy_2 = tmp_38;
  i_18 = 0;
  while (true) {
    if (!((i_18 < (str_2->length)))) {
      break;
    }
    (copy_2->arr[i_18]) = (str_2->arr[i_18]);
    i_18 = (i_18 + 1);
  }
  return copy_2;
}

int strlen (SPLArray_char* str_3) {
  int res_14;
  int i_19;
  
  i_19 = 0;
  while (true) {
    if (!(((i_19 < (str_3->length)) && (!((str_3->arr[i_19]) == ((char) 0)))))) {
      break;
    }
    i_19 = (i_19 + 1);
  }
  return i_19;
}

/*
 * Main Function, here for compilability
 */
int main(int argc, char *argv[]) {
  assert(argc <= 2);
  int s = 0;
  if (argc > 1) {
    for(s = 0; argv[1][s] != 0; s++) { }
    s++;
  }
  SPLArray_char* a = newSPLArray_char(s);
  for(int i = 0; i < s; i++) {
    a->arr[i] = argv[1][i];
  }
  return Main(a);
}

