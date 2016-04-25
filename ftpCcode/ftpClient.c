/*
 * Includes
 */
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <netinet/in.h>
#include <fcntl.h>

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
bool allo_help (int size, int cmdFd);
SPLArray_char* askFilename ();
struct SocketAddressIP4* askIP (SPLArray_char* port);
int atoiFrom (SPLArray_char* str, int startIdx);
int atoiG (SPLArray_char* str_1);
bool authenticate (int cmdFd_1);
bool bind4 (int fd_2, struct SocketAddressIP4* address_2);
bool bind6 (int fd_3, struct SocketAddressIP6* address_3);
bool checkServerResponsePASS (SPLArray_char* response);
bool checkServerResponseUSER (SPLArray_char* response_1);
bool checkServerResponse_200 (SPLArray_char* response_2);
bool checkServerResponse_200_150 (SPLArray_char* response_3);
bool checkServerResponse_200_226_250 (SPLArray_char* response_4);
bool checkServerResponse_213 (SPLArray_char* response_5);
int client (bool upload_1);
SPLArray_char* concat (SPLArray_char* str1, SPLArray_char* str2);
bool connect4 (int fd_5, struct SocketAddressIP4* address_4);
bool connect6 (int fd_6, struct SocketAddressIP6* address_5);
int connectTo (struct SocketAddressIP4* addr);
SPLArray_char* copy_byte_slice (SPLArray_char* a, int start, int end);
int create_socket (int inet_type, int socket_type, int protocol);
int doWeUpload ();
bool downloadFile (int cmdFd_2, int dataFD, SPLArray_char* filename_2);
bool equals (SPLArray_char* first, SPLArray_char* second);
int fileSize (SPLArray_char* pathname);
int gclose (int fd_9);
struct SocketAddressIP4* get_address4 (SPLArray_char* node, SPLArray_char* service);
struct SocketAddressIP6* get_address6 (SPLArray_char* node_1, SPLArray_char* service_1);
int ggets (SPLArray_char* buffer_1);
bool glisten (int fd_10, int backlog);
int gopen (SPLArray_char* pathname_1, int flags);
bool gputs (SPLArray_char* buffer_2);
int gread (int fd_12, SPLArray_char* buffer_3);
int greadOffset (int fd_13, SPLArray_char* buffer_4, int offset);
int gstrcat (SPLArray_char* str1_1, SPLArray_char* str2_1);
int gstrcmp (SPLArray_char* s1, SPLArray_char* s2);
SPLArray_char* gstrdup (SPLArray_char* str_2);
int gstrlen (SPLArray_char* str_3);
int gwrite (int fd_14, SPLArray_char* buffer_5);
int gwrite2 (int fd_15, SPLArray_char* buffer_6, int size_3);
bool retrHelp (int cmdFd_3, SPLArray_char* filename_3, int cmdSize_1);
int setupDataConnection (int cmdFd_4, struct SocketAddressIP4* address_8, SPLArray_char* port_2);
int sizeHelp (int cmdFd_5, SPLArray_char* filename_4, int cmdSize_2);
bool store_send_help (int cmdFd_6, SPLArray_char* filename_5);
SPLArray_char* strconcat (SPLArray_char* str1_2, SPLArray_char* str2_2);
int tcp_recv (int fd_16, SPLArray_char* msg);
int tcp_send (int fd_17, SPLArray_char* msg_1, int len);
int udp_recv4 (int fd_18, SPLArray_char* msg_2, struct SocketAddressIP4* from);
int udp_recv6 (int fd_19, SPLArray_char* msg_3, struct SocketAddressIP6* from_1);
int udp_send4 (int fd_20, SPLArray_char* msg_4, int len_1, struct SocketAddressIP4* address_9);
int udp_send6 (int fd_21, SPLArray_char* msg_5, int len_2, struct SocketAddressIP6* address_10);
bool uploadFile (int cmdFd_7, int dataFD_2, SPLArray_char* filename_6);

int Main (SPLArray_char* args) {
  int res;
  int upload;
  
  upload = doWeUpload();
  if ((upload == 1)) {
    res = client(true);
  } else {
    if ((upload == 0)) {
      res = client(false);
    } else {
      res = (-1);
    }
  }
  return res;
}

bool allo_help (int size, int cmdFd) {
  bool success;
  SPLArray_char* tmp_2;
  SPLArray_char* tmp_1;
  SPLArray_char* tmp;
  int sent;
  SPLArray_char* sendMsg;
  SPLArray_char* okMsg;
  int ok;
  int copied;
  bool checked;
  SPLArray_char* alloSize;
  
  tmp = newSPLArray_char( 2);
  alloSize = tmp;
  (alloSize->arr[0]) = ((char) size);
  (alloSize->arr[1]) = ((char) 0);
  tmp_1 = newSPLArray_char( 6);
  sendMsg = tmp_1;
  (sendMsg->arr[0]) = ((char) 65);
  (sendMsg->arr[1]) = ((char) 76);
  (sendMsg->arr[2]) = ((char) 76);
  (sendMsg->arr[3]) = ((char) 79);
  (sendMsg->arr[4]) = ((char) 32);
  (sendMsg->arr[5]) = ((char) 0);
  copied = gstrcat(alloSize, sendMsg);
  sent = tcp_send(cmdFd, sendMsg, 7);
  free(sendMsg);
  
  free(alloSize);
  
  tmp_2 = newSPLArray_char( 4);
  okMsg = tmp_2;
  ok = tcp_recv(cmdFd, okMsg);
  checked = checkServerResponse_200(okMsg);
  free(okMsg);
  
  if ((!checked)) {
    return false;
  }
  return true;
}

SPLArray_char* askFilename () {
  SPLArray_char* fn;
  SPLArray_char* tmp_4;
  SPLArray_char* tmp_3;
  SPLArray_char* text;
  bool putted;
  int numChars;
  SPLArray_char* filename;
  
  tmp_3 = newSPLArray_char( 100);
  filename = tmp_3;
  tmp_4 = newSPLArray_char( 24);
  text = tmp_4;
  (text->arr[0]) = ((char) 105);
  (text->arr[1]) = ((char) 110);
  (text->arr[2]) = ((char) 112);
  (text->arr[3]) = ((char) 117);
  (text->arr[4]) = ((char) 116);
  (text->arr[5]) = ((char) 32);
  (text->arr[6]) = ((char) 116);
  (text->arr[7]) = ((char) 104);
  (text->arr[8]) = ((char) 101);
  (text->arr[9]) = ((char) 32);
  (text->arr[10]) = ((char) 102);
  (text->arr[11]) = ((char) 105);
  (text->arr[12]) = ((char) 108);
  (text->arr[13]) = ((char) 101);
  (text->arr[14]) = ((char) 32);
  (text->arr[15]) = ((char) 110);
  (text->arr[16]) = ((char) 97);
  (text->arr[17]) = ((char) 109);
  (text->arr[18]) = ((char) 101);
  (text->arr[19]) = ((char) 58);
  (text->arr[20]) = ((char) 0);
  putted = gputs(text);
  free(text);
  
  if ((!putted)) {
    free(filename);
    
    return NULL;
  }
  numChars = ggets(filename);
  if (((numChars >= 100) || (numChars <= 1))) {
    free(filename);
    
    return NULL;
  }
  (filename->arr[(numChars - 1)]) = ((char) 0);
  return filename;
}

struct SocketAddressIP4* askIP (SPLArray_char* port) {
  struct SocketAddressIP4* ip;
  SPLArray_char* writtenPrompt;
  bool written;
  SPLArray_char* tmp_6;
  SPLArray_char* tmp_5;
  int numChars_1;
  SPLArray_char* getip;
  struct SocketAddressIP4* dataAddr;
  
  tmp_5 = newSPLArray_char( 46);
  writtenPrompt = tmp_5;
  (writtenPrompt->arr[0]) = ((char) 69);
  (writtenPrompt->arr[1]) = ((char) 110);
  (writtenPrompt->arr[2]) = ((char) 116);
  (writtenPrompt->arr[3]) = ((char) 101);
  (writtenPrompt->arr[4]) = ((char) 114);
  (writtenPrompt->arr[5]) = ((char) 32);
  (writtenPrompt->arr[6]) = ((char) 73);
  (writtenPrompt->arr[7]) = ((char) 80);
  (writtenPrompt->arr[8]) = ((char) 32);
  (writtenPrompt->arr[9]) = ((char) 111);
  (writtenPrompt->arr[10]) = ((char) 102);
  (writtenPrompt->arr[11]) = ((char) 32);
  (writtenPrompt->arr[12]) = ((char) 115);
  (writtenPrompt->arr[13]) = ((char) 101);
  (writtenPrompt->arr[14]) = ((char) 114);
  (writtenPrompt->arr[15]) = ((char) 118);
  (writtenPrompt->arr[16]) = ((char) 101);
  (writtenPrompt->arr[17]) = ((char) 114);
  (writtenPrompt->arr[18]) = ((char) 32);
  (writtenPrompt->arr[19]) = ((char) 40);
  (writtenPrompt->arr[20]) = ((char) 104);
  (writtenPrompt->arr[21]) = ((char) 105);
  (writtenPrompt->arr[22]) = ((char) 116);
  (writtenPrompt->arr[23]) = ((char) 32);
  (writtenPrompt->arr[24]) = ((char) 101);
  (writtenPrompt->arr[25]) = ((char) 110);
  (writtenPrompt->arr[26]) = ((char) 116);
  (writtenPrompt->arr[27]) = ((char) 101);
  (writtenPrompt->arr[28]) = ((char) 114);
  (writtenPrompt->arr[29]) = ((char) 32);
  (writtenPrompt->arr[30]) = ((char) 102);
  (writtenPrompt->arr[31]) = ((char) 111);
  (writtenPrompt->arr[32]) = ((char) 114);
  (writtenPrompt->arr[33]) = ((char) 32);
  (writtenPrompt->arr[34]) = ((char) 108);
  (writtenPrompt->arr[35]) = ((char) 111);
  (writtenPrompt->arr[36]) = ((char) 99);
  (writtenPrompt->arr[37]) = ((char) 97);
  (writtenPrompt->arr[38]) = ((char) 108);
  (writtenPrompt->arr[39]) = ((char) 104);
  (writtenPrompt->arr[40]) = ((char) 111);
  (writtenPrompt->arr[41]) = ((char) 115);
  (writtenPrompt->arr[42]) = ((char) 116);
  (writtenPrompt->arr[43]) = ((char) 41);
  (writtenPrompt->arr[44]) = ((char) 58);
  (writtenPrompt->arr[45]) = ((char) 0);
  written = gputs(writtenPrompt);
  free(writtenPrompt);
  
  tmp_6 = newSPLArray_char( 50);
  getip = tmp_6;
  numChars_1 = ggets(getip);
  dataAddr = NULL;
  if ((numChars_1 < 1)) {
    free(getip);
    
    return dataAddr;
  }
  (getip->arr[(numChars_1 - 1)]) = ((char) 0);
  if ((!(numChars_1 == 1))) {
    dataAddr = get_address4(getip, port);
  } else {
    dataAddr = get_address4(NULL, port);
  }
  free(getip);
  
  return dataAddr;
}

int atoiFrom (SPLArray_char* str, int startIdx) {
  int res_1;
  bool isPositive;
  int i;
  bool foundStart;
  bool foundEnd;
  int digit;
  
  res_1 = 0;
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
      res_1 = (res_1 * 10);
      res_1 = (res_1 + digit);
      i = (i + 1);
    } else {
      foundEnd = true;
    }
  }
  if ((!isPositive)) {
    res_1 = ((-1) * res_1);
  }
  return res_1;
}

int atoiG (SPLArray_char* str_1) {
  int res_2;
  res_2 = atoiFrom(str_1, 0);
  return res_2;
  return res_2;
}

bool authenticate (int cmdFd_1) {
  bool success_1;
  SPLArray_char* userMsg;
  SPLArray_char* tmp_10;
  SPLArray_char* tmp_9;
  SPLArray_char* tmp_8;
  SPLArray_char* tmp_7;
  int sent_1;
  SPLArray_char* passMsg;
  SPLArray_char* okMsg_1;
  int ok_1;
  bool checked_1;
  
  tmp_7 = newSPLArray_char( 12);
  userMsg = tmp_7;
  (userMsg->arr[0]) = ((char) 85);
  (userMsg->arr[1]) = ((char) 83);
  (userMsg->arr[2]) = ((char) 69);
  (userMsg->arr[3]) = ((char) 82);
  (userMsg->arr[4]) = ((char) 32);
  (userMsg->arr[5]) = ((char) 112);
  (userMsg->arr[6]) = ((char) 111);
  (userMsg->arr[7]) = ((char) 116);
  (userMsg->arr[8]) = ((char) 97);
  (userMsg->arr[9]) = ((char) 116);
  (userMsg->arr[10]) = ((char) 111);
  (userMsg->arr[11]) = ((char) 0);
  sent_1 = tcp_send(cmdFd_1, userMsg, 12);
  free(userMsg);
  
  tmp_8 = newSPLArray_char( 4);
  okMsg_1 = tmp_8;
  ok_1 = tcp_recv(cmdFd_1, okMsg_1);
  checked_1 = checkServerResponseUSER(okMsg_1);
  free(okMsg_1);
  
  if ((!checked_1)) {
    return false;
  }
  tmp_9 = newSPLArray_char( 15);
  passMsg = tmp_9;
  (passMsg->arr[0]) = ((char) 80);
  (passMsg->arr[1]) = ((char) 65);
  (passMsg->arr[2]) = ((char) 83);
  (passMsg->arr[3]) = ((char) 83);
  (passMsg->arr[4]) = ((char) 32);
  (passMsg->arr[5]) = ((char) 97);
  (passMsg->arr[6]) = ((char) 110);
  (passMsg->arr[7]) = ((char) 111);
  (passMsg->arr[8]) = ((char) 110);
  (passMsg->arr[9]) = ((char) 121);
  (passMsg->arr[10]) = ((char) 109);
  (passMsg->arr[11]) = ((char) 111);
  (passMsg->arr[12]) = ((char) 117);
  (passMsg->arr[13]) = ((char) 115);
  (passMsg->arr[14]) = ((char) 0);
  sent_1 = tcp_send(cmdFd_1, passMsg, 15);
  free(passMsg);
  
  tmp_10 = newSPLArray_char( 4);
  okMsg_1 = tmp_10;
  ok_1 = tcp_recv(cmdFd_1, okMsg_1);
  checked_1 = checkServerResponsePASS(okMsg_1);
  free(okMsg_1);
  
  if ((!checked_1)) {
    return false;
  }
  return true;
}

bool checkServerResponsePASS (SPLArray_char* response) {
  bool success_4;
  int ack;
  
  ack = atoiG(response);
  if (((((ack == 200) || (ack == 202)) || (ack == 230)) || (ack == 234))) {
    success_4 = true;
  } else {
    success_4 = false;
  }
  return success_4;
}

bool checkServerResponseUSER (SPLArray_char* response_1) {
  bool success_5;
  int ack_1;
  
  ack_1 = atoiG(response_1);
  if (((((ack_1 == 200) || (ack_1 == 230)) || (ack_1 == 234)) || (ack_1 == 331))) {
    success_5 = true;
  } else {
    success_5 = false;
  }
  return success_5;
}

bool checkServerResponse_200 (SPLArray_char* response_2) {
  bool success_6;
  int ack_2;
  
  ack_2 = atoiG(response_2);
  if ((ack_2 == 200)) {
    return true;
  } else {
    return false;
  }
  return success_6;
}

bool checkServerResponse_200_150 (SPLArray_char* response_3) {
  bool success_7;
  int ack_3;
  
  ack_3 = atoiG(response_3);
  if (((ack_3 == 200) || (ack_3 == 150))) {
    success_7 = true;
  } else {
    success_7 = false;
  }
  return success_7;
}

bool checkServerResponse_200_226_250 (SPLArray_char* response_4) {
  bool success_8;
  int ack_4;
  
  ack_4 = atoiG(response_4);
  if ((((ack_4 == 200) || (ack_4 == 226)) || (ack_4 == 250))) {
    success_8 = true;
  } else {
    success_8 = false;
  }
  return success_8;
}

bool checkServerResponse_213 (SPLArray_char* response_5) {
  bool success_9;
  int ack_5;
  
  ack_5 = atoiG(response_5);
  if ((ack_5 == 213)) {
    return true;
  } else {
    return false;
  }
  return success_9;
}

int client (bool upload_1) {
  int res_3;
  SPLArray_char* tmp_12;
  SPLArray_char* tmp_11;
  bool success_10;
  int sent_2;
  struct SocketAddressIP4* remoteAddr;
  SPLArray_char* quitMsg;
  SPLArray_char* port_1;
  SPLArray_char* filename_1;
  int fd_4;
  struct SocketAddressIP4* dataAddr_1;
  int connectedDataFD;
  int closed_3;
  int closed_2;
  int closed_1;
  int closed;
  int closeFD;
  int closeConn;
  bool authenticated;
  
  tmp_11 = newSPLArray_char( 5);
  port_1 = tmp_11;
  (port_1->arr[0]) = ((char) 52);
  (port_1->arr[1]) = ((char) 52);
  (port_1->arr[2]) = ((char) 52);
  (port_1->arr[3]) = ((char) 52);
  (port_1->arr[4]) = ((char) 0);
  remoteAddr = askIP(port_1);
  if ((remoteAddr == NULL)) {
    free(port_1);
    
    return (-1);
  }
  fd_4 = connectTo(remoteAddr);
  free(remoteAddr);
  
  if ((fd_4 == (-1))) {
    free(port_1);
    
    return (-1);
  }
  (port_1->arr[0]) = ((char) 52);
  (port_1->arr[1]) = ((char) 52);
  (port_1->arr[2]) = ((char) 52);
  (port_1->arr[3]) = ((char) 48);
  (port_1->arr[4]) = ((char) 0);
  dataAddr_1 = askIP(port_1);
  if ((dataAddr_1 == NULL)) {
    free(port_1);
    
    return (-1);
  }
  connectedDataFD = setupDataConnection(fd_4, dataAddr_1, port_1);
  free(port_1);
  
  free(dataAddr_1);
  
  if ((connectedDataFD == (-1))) {
    closed = gclose(fd_4);
    return 3;
  }
  authenticated = authenticate(fd_4);
  if ((!authenticated)) {
    closed_1 = gclose(fd_4);
    closed_1 = gclose(connectedDataFD);
    return 4;
  }
  filename_1 = askFilename();
  if ((filename_1 == NULL)) {
    closed_2 = gclose(fd_4);
    closed_2 = gclose(connectedDataFD);
    return 5;
  }
  success_10 = false;
  if (upload_1) {
    success_10 = uploadFile(fd_4, connectedDataFD, filename_1);
  } else {
    success_10 = downloadFile(fd_4, connectedDataFD, filename_1);
  }
  free(filename_1);
  
  if ((!success_10)) {
    closed_3 = gclose(fd_4);
    closed_3 = gclose(connectedDataFD);
    return 6;
  }
  closeConn = gclose(connectedDataFD);
  if ((closeConn < 0)) {
    return 22;
  }
  tmp_12 = newSPLArray_char( 5);
  quitMsg = tmp_12;
  (quitMsg->arr[0]) = ((char) 81);
  (quitMsg->arr[1]) = ((char) 85);
  (quitMsg->arr[2]) = ((char) 73);
  (quitMsg->arr[3]) = ((char) 84);
  (quitMsg->arr[4]) = ((char) 0);
  sent_2 = tcp_send(fd_4, quitMsg, 5);
  free(quitMsg);
  
  closeFD = gclose(fd_4);
  if ((closeFD < 0)) {
    return 21;
  }
  return 0;
}

SPLArray_char* concat (SPLArray_char* str1, SPLArray_char* str2) {
  SPLArray_char* res_4;
  SPLArray_char* tmp_13;
  int i_2;
  SPLArray_char* copy;
  
  
  tmp_13 = newSPLArray_char( ((str1->length) + (str2->length)));
  copy = tmp_13;
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

int connectTo (struct SocketAddressIP4* addr) {
  int fd_7;
  bool tmp_14;
  
  fd_7 = create_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((fd_7 == (-1))) {
    return (-1);
  }
  tmp_14 = connect4(fd_7, addr);
  if (tmp_14) {
    return fd_7;
  } else {
    return (-1);
  }
  return fd_7;
}

SPLArray_char* copy_byte_slice (SPLArray_char* a, int start, int end) {
  SPLArray_char* b;
  SPLArray_char* tmp_15;
  int i_5;
  int finalLength;
  
  finalLength = (end - start);
  tmp_15 = newSPLArray_char( finalLength);
  b = tmp_15;
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

int doWeUpload () {
  int res_5;
  bool written_1;
  SPLArray_char* updown;
  SPLArray_char* uChar;
  int tmp_20;
  SPLArray_char* tmp_19;
  SPLArray_char* tmp_18;
  SPLArray_char* tmp_17;
  SPLArray_char* tmp_16;
  SPLArray_char* text_1;
  int numChars_2;
  SPLArray_char* copy_1;
  
  tmp_16 = newSPLArray_char( 30);
  updown = tmp_16;
  tmp_17 = newSPLArray_char( 28);
  text_1 = tmp_17;
  (text_1->arr[0]) = ((char) 117);
  (text_1->arr[1]) = ((char) 112);
  (text_1->arr[2]) = ((char) 108);
  (text_1->arr[3]) = ((char) 111);
  (text_1->arr[4]) = ((char) 97);
  (text_1->arr[5]) = ((char) 100);
  (text_1->arr[6]) = ((char) 32);
  (text_1->arr[7]) = ((char) 40);
  (text_1->arr[8]) = ((char) 117);
  (text_1->arr[9]) = ((char) 41);
  (text_1->arr[10]) = ((char) 32);
  (text_1->arr[11]) = ((char) 111);
  (text_1->arr[12]) = ((char) 114);
  (text_1->arr[13]) = ((char) 32);
  (text_1->arr[14]) = ((char) 100);
  (text_1->arr[15]) = ((char) 111);
  (text_1->arr[16]) = ((char) 119);
  (text_1->arr[17]) = ((char) 110);
  (text_1->arr[18]) = ((char) 108);
  (text_1->arr[19]) = ((char) 111);
  (text_1->arr[20]) = ((char) 97);
  (text_1->arr[21]) = ((char) 100);
  (text_1->arr[22]) = ((char) 32);
  (text_1->arr[23]) = ((char) 40);
  (text_1->arr[24]) = ((char) 100);
  (text_1->arr[25]) = ((char) 41);
  (text_1->arr[26]) = ((char) 58);
  (text_1->arr[27]) = ((char) 0);
  written_1 = gputs(text_1);
  free(text_1);
  
  if ((!written_1)) {
    free(updown);
    
    return (-1);
  } else {
    numChars_2 = ggets(updown);
    if ((numChars_2 == 2)) {
      tmp_18 = newSPLArray_char( 2);
      copy_1 = tmp_18;
      (copy_1->arr[0]) = (updown->arr[0]);
      (copy_1->arr[1]) = ((char) 0);
      free(updown);
      
      tmp_19 = newSPLArray_char( 2);
      uChar = tmp_19;
      (uChar->arr[0]) = ((char) 117);
      (uChar->arr[1]) = ((char) 0);
      tmp_20 = gstrcmp(uChar, copy_1);
      if ((tmp_20 == 0)) {
        free(uChar);
        
        free(copy_1);
        
        return 1;
      } else {
        free(uChar);
        
        free(copy_1);
        
        return 0;
      }
    } else {
      free(updown);
      
      return (-1);
    }
  }
  return res_5;
}

bool downloadFile (int cmdFd_2, int dataFD, SPLArray_char* filename_2) {
  bool success_13;
  int written_2;
  SPLArray_char* tmp_22;
  SPLArray_char* tmp_21;
  int size_1;
  int saveFD;
  bool retrDone;
  int recvData;
  SPLArray_char* okMsg_2;
  int ok_2;
  int cmdSize;
  int close;
  bool checked_2;
  SPLArray_char* buffer;
  
  if ((((filename_2->length) <= 0) || ((filename_2->length) > (65535 - 6)))) {
    return false;
  }
  cmdSize = (6 + (filename_2->length));
  size_1 = sizeHelp(cmdFd_2, filename_2, cmdSize);
  if ((size_1 < 0)) {
    return false;
  }
  tmp_21 = newSPLArray_char( size_1);
  buffer = tmp_21;
  retrDone = retrHelp(cmdFd_2, filename_2, cmdSize);
  if ((!retrDone)) {
    free(buffer);
    
    return false;
  }
  recvData = tcp_recv(dataFD, buffer);
  tmp_22 = newSPLArray_char( 4);
  okMsg_2 = tmp_22;
  ok_2 = tcp_recv(cmdFd_2, okMsg_2);
  checked_2 = checkServerResponse_200_226_250(okMsg_2);
  free(okMsg_2);
  
  if ((!checked_2)) {
    free(buffer);
    
    return false;
  }
  if ((recvData < 0)) {
    free(buffer);
    
    return false;
  }
  saveFD = gopen(filename_2, ((O_CREAT | O_WRONLY) | O_TRUNC));
  if ((saveFD < 0)) {
    free(buffer);
    
    return false;
  }
  written_2 = gwrite(saveFD, buffer);
  free(buffer);
  
  if ((written_2 < 0)) {
    return false;
  }
  close = gclose(saveFD);
  return true;
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

int gstrcat (SPLArray_char* str1_1, SPLArray_char* str2_1) {
  int res_7;
  int l2;
  int l1;
  int i_11;
  int copy_size;
  
  l1 = gstrlen(str1_1);
  l2 = gstrlen(str2_1);
  copy_size = ((str2_1->length) - l2);
  if ((copy_size > l1)) {
    copy_size = l1;
  }
  i_11 = 0;
  while (true) {
    if (!((i_11 < copy_size))) {
      break;
    }
    (str2_1->arr[(i_11 + l2)]) = (str1_1->arr[i_11]);
    i_11 = (i_11 + 1);
  }
  if (((l2 + copy_size) < (str2_1->length))) {
    (str2_1->arr[(l2 + copy_size)]) = ((char) 0);
  }
  return copy_size;
}

int gstrcmp (SPLArray_char* s1, SPLArray_char* s2) {
  int res_8;
  int i_13;
  
  i_13 = 0;
  while (true) {
    if (!((((i_13 < (s1->length)) && (i_13 < (s2->length))) && ((s1->arr[i_13]) == (s2->arr[i_13]))))) {
      break;
    }
    i_13 = (i_13 + 1);
  }
  if (((i_13 >= (s1->length)) && (i_13 >= (s2->length)))) {
    return 0;
  } else {
    if ((i_13 >= (s1->length))) {
      return (-1);
    } else {
      if ((i_13 >= (s2->length))) {
        return 1;
      } else {
        if (((s1->arr[i_13]) < (s2->arr[i_13]))) {
          return (-1);
        } else {
          return 1;
        }
      }
    }
  }
  return res_8;
}

SPLArray_char* gstrdup (SPLArray_char* str_2) {
  SPLArray_char* res_9;
  SPLArray_char* tmp_23;
  int i_15;
  SPLArray_char* copy_2;
  
  tmp_23 = newSPLArray_char( (str_2->length));
  copy_2 = tmp_23;
  i_15 = 0;
  while (true) {
    if (!((i_15 < (str_2->length)))) {
      break;
    }
    (copy_2->arr[i_15]) = (str_2->arr[i_15]);
    i_15 = (i_15 + 1);
  }
  return copy_2;
}

int gstrlen (SPLArray_char* str_3) {
  int res_10;
  int i_16;
  
  i_16 = 0;
  while (true) {
    if (!(((i_16 < (str_3->length)) && (!((str_3->arr[i_16]) == ((char) 0)))))) {
      break;
    }
    i_16 = (i_16 + 1);
  }
  return i_16;
}

bool retrHelp (int cmdFd_3, SPLArray_char* filename_3, int cmdSize_1) {
  bool success_16;
  SPLArray_char* tmp_25;
  SPLArray_char* tmp_24;
  int sent_3;
  SPLArray_char* recvMsg;
  SPLArray_char* okMsg_3;
  int ok_3;
  int copied_1;
  bool checked_3;
  
  tmp_24 = newSPLArray_char( cmdSize_1);
  recvMsg = tmp_24;
  (recvMsg->arr[0]) = ((char) 82);
  (recvMsg->arr[1]) = ((char) 69);
  (recvMsg->arr[2]) = ((char) 84);
  (recvMsg->arr[3]) = ((char) 82);
  (recvMsg->arr[4]) = ((char) 32);
  (recvMsg->arr[5]) = ((char) 0);
  copied_1 = gstrcat(filename_3, recvMsg);
  sent_3 = tcp_send(cmdFd_3, recvMsg, cmdSize_1);
  free(recvMsg);
  
  tmp_25 = newSPLArray_char( 4);
  okMsg_3 = tmp_25;
  ok_3 = tcp_recv(cmdFd_3, okMsg_3);
  checked_3 = checkServerResponse_200_150(okMsg_3);
  free(okMsg_3);
  
  if ((!checked_3)) {
    return false;
  }
  return true;
}

int setupDataConnection (int cmdFd_4, struct SocketAddressIP4* address_8, SPLArray_char* port_2) {
  int connectedDataFD_1;
  SPLArray_char* tmp_26;
  int sent_4;
  SPLArray_char* portMsg;
  bool datalistening;
  int dataFD_1;
  int copied_2;
  int closeData;
  bool bound;
  
  dataFD_1 = create_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((dataFD_1 == (-1))) {
    return (-1);
  }
  bound = bind4(dataFD_1, address_8);
  if ((!bound)) {
    return (-1);
  }
  datalistening = glisten(dataFD_1, 10);
  if ((!datalistening)) {
    return (-1);
  }
  if ((((port_2->length) < 0) || ((port_2->length) > (65535 - 6)))) {
    return (-1);
  }
  tmp_26 = newSPLArray_char( (6 + (port_2->length)));
  portMsg = tmp_26;
  (portMsg->arr[0]) = ((char) 80);
  (portMsg->arr[1]) = ((char) 79);
  (portMsg->arr[2]) = ((char) 82);
  (portMsg->arr[3]) = ((char) 84);
  (portMsg->arr[4]) = ((char) 32);
  (portMsg->arr[5]) = ((char) 0);
  copied_2 = gstrcat(port_2, portMsg);
  sent_4 = tcp_send(cmdFd_4, portMsg, (portMsg->length));
  free(portMsg);
  
  if ((!(sent_4 == (portMsg->length)))) {
    return (-1);
  }
  connectedDataFD_1 = accept4(dataFD_1, address_8);
  closeData = gclose(dataFD_1);
  return connectedDataFD_1;
}

int sizeHelp (int cmdFd_5, SPLArray_char* filename_4, int cmdSize_2) {
  int success_17;
  SPLArray_char* tmp_28;
  SPLArray_char* tmp_27;
  SPLArray_char* sizeMsg;
  SPLArray_char* sizeBuff;
  int size_4;
  int sent_5;
  int recvData_1;
  int copied_3;
  bool checked_4;
  
  tmp_27 = newSPLArray_char( cmdSize_2);
  sizeMsg = tmp_27;
  (sizeMsg->arr[0]) = ((char) 83);
  (sizeMsg->arr[1]) = ((char) 73);
  (sizeMsg->arr[2]) = ((char) 90);
  (sizeMsg->arr[3]) = ((char) 69);
  (sizeMsg->arr[4]) = ((char) 32);
  (sizeMsg->arr[5]) = ((char) 0);
  copied_3 = gstrcat(filename_4, sizeMsg);
  sent_5 = tcp_send(cmdFd_5, sizeMsg, cmdSize_2);
  free(sizeMsg);
  
  tmp_28 = newSPLArray_char( 128);
  sizeBuff = tmp_28;
  recvData_1 = tcp_recv(cmdFd_5, sizeBuff);
  checked_4 = checkServerResponse_213(sizeBuff);
  if ((!checked_4)) {
    free(sizeBuff);
    
    return (-1);
  }
  size_4 = atoiFrom(sizeBuff, 4);
  free(sizeBuff);
  
  if (((size_4 <= 0) || (size_4 > 65535))) {
    return (-1);
  }
  return size_4;
}

bool store_send_help (int cmdFd_6, SPLArray_char* filename_5) {
  bool success_18;
  SPLArray_char* tmp_30;
  SPLArray_char* tmp_29;
  int sent_6;
  SPLArray_char* sendMsg_1;
  SPLArray_char* okMsg_4;
  int ok_4;
  int copied_4;
  int commandSize;
  bool checked_5;
  
  commandSize = ((filename_5->length) + 6);
  tmp_29 = newSPLArray_char( commandSize);
  sendMsg_1 = tmp_29;
  (sendMsg_1->arr[0]) = ((char) 83);
  (sendMsg_1->arr[1]) = ((char) 84);
  (sendMsg_1->arr[2]) = ((char) 79);
  (sendMsg_1->arr[3]) = ((char) 82);
  (sendMsg_1->arr[4]) = ((char) 32);
  (sendMsg_1->arr[5]) = ((char) 0);
  copied_4 = gstrcat(filename_5, sendMsg_1);
  sent_6 = tcp_send(cmdFd_6, sendMsg_1, commandSize);
  free(sendMsg_1);
  
  tmp_30 = newSPLArray_char( 4);
  okMsg_4 = tmp_30;
  ok_4 = tcp_recv(cmdFd_6, okMsg_4);
  checked_5 = checkServerResponse_200_150(okMsg_4);
  free(okMsg_4);
  
  if ((!checked_5)) {
    return false;
  }
  return true;
}

SPLArray_char* strconcat (SPLArray_char* str1_2, SPLArray_char* str2_2) {
  SPLArray_char* res_11;
  SPLArray_char* tmp_31;
  int l2_1;
  int l1_1;
  int i_19;
  SPLArray_char* copy_3;
  
  l1_1 = gstrlen(str1_2);
  l2_1 = gstrlen(str2_2);
  
  tmp_31 = newSPLArray_char( (l1_1 + l2_1));
  copy_3 = tmp_31;
  i_19 = 0;
  while (true) {
    if (!((i_19 < l1_1))) {
      break;
    }
    (copy_3->arr[i_19]) = (str1_2->arr[i_19]);
    i_19 = (i_19 + 1);
  }
  while (true) {
    if (!((i_19 < (l1_1 + l2_1)))) {
      break;
    }
    (copy_3->arr[i_19]) = (str2_2->arr[(i_19 - l1_1)]);
    i_19 = (i_19 + 1);
  }
  return copy_3;
}

bool uploadFile (int cmdFd_7, int dataFD_2, SPLArray_char* filename_6) {
  bool success_19;
  SPLArray_char* tmp_33;
  SPLArray_char* tmp_32;
  bool stored;
  int size_5;
  int sentData;
  int read;
  int opened;
  SPLArray_char* okMsg_5;
  int ok_5;
  int close_1;
  bool checked_6;
  SPLArray_char* buffer_7;
  bool allo_check;
  
  size_5 = fileSize(filename_6);
  if (((size_5 < 0) || (size_5 > 65535))) {
    return false;
  }
  allo_check = allo_help(size_5, cmdFd_7);
  if ((!allo_check)) {
    return false;
  }
  opened = gopen(filename_6, (O_CREAT | O_RDONLY));
  if ((opened < 0)) {
    return false;
  }
  tmp_32 = newSPLArray_char( size_5);
  buffer_7 = tmp_32;
  read = gread(opened, buffer_7);
  if ((read < 0)) {
    free(buffer_7);
    
    return false;
  }
  stored = store_send_help(cmdFd_7, filename_6);
  if ((!stored)) {
    free(buffer_7);
    
    return false;
  }
  sentData = tcp_send(dataFD_2, buffer_7, size_5);
  tmp_33 = newSPLArray_char( 4);
  okMsg_5 = tmp_33;
  ok_5 = tcp_recv(cmdFd_7, okMsg_5);
  checked_6 = checkServerResponse_200_226_250(okMsg_5);
  free(okMsg_5);
  
  free(buffer_7);
  
  if ((!checked_6)) {
    return false;
  }
  close_1 = gclose(opened);
  if ((sentData == size_5)) {
    return true;
  } else {
    return false;
  }
  return success_19;
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

