/**
  *	@file test_client.c
  *	@brief	SoT Client test code
  *	@author	James
  *	@date	2016.03.01
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "sot_key.h"
#include "sot_aes.h"
#include "sot_key_gen.h"

#define BUFSIZE 			256
#define	ENCRYPT_KEY_SIZE	16
#define	TEXTSIZE			256

size_t 	sendData(int Sock, BYTE *SendStr,  size_t SendStrLen);
size_t 	dataEncrypt(BYTE* DeviceKey, BYTE* Src, BYTE* Des);

int main (int argc, char *argv[]){
	if (argc < 3 || argc > 4)
		printf("Usage : <Server Address> <Server Port> <Unique Key> <Device Key>\n");

	char *ServIP = argv[1];						/**< Server IP */
	BYTE *DeviceKey = argv[4];						/**< 가변형 Device key 저장 벼수 */
	BYTE *UniqueKey = argv[3];					/**< Device Unique Key(etc. Serial Number) */

	in_port_t	ServPort = atoi(argv[2]);				/**< Port */
	size_t		SendStrLen;						/**< 입력 받은 데이터의 길이 */

	/// SoT device auth key 를 수신할 변수 or File name 현재는 디바이스 키 지만 다음에는 파일에 저장 하는 형태

	BYTE SendData[BUFSIZE];							/**< 전송할 인증 문자열  변수 */
	BYTE SendStr[BUFSIZE];							/**< 전송할 입력 데이터를 저장할 변수 */

	/// 소켓 생성 
	int Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Sock < 0)
		perror("socket() failed\n");

	/// 서버 주소 구조체 생성
	struct sockaddr_in ServAddr;
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;

	/// 주소 변환
	int RtnVal = inet_pton(AF_INET, ServIP, &ServAddr.sin_addr.s_addr);
	if (RtnVal == 0)
		perror("inet_pton() failed\n");
	else if (RtnVal < 0)
		perror("inet_pton() failed\n");
	ServAddr.sin_port = htons(ServPort);

	/// 서버 커넥트
	if (connect(Sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
		perror("connect() failed\n");

	sprintf(SendData, "{\'product_key\':\'%s\',\'device_key\':\'%s\'}", UniqueKey, DeviceKey);
	puts(SendData);
	size_t SendDataLen = strlen(SendData);

	// 서버에 데이터 전송
	ssize_t NumBytes = send(Sock, SendData, SendDataLen, 0);
	if(NumBytes < 0){
		perror("send() failed\n");
		exit(1);
	}

	// 서버로 부터 동일한 문자열 수신
	unsigned int TotalBytesRcvd = 0;
	fputs("Recevied: ", stdout);
	while (NumBytes != -1){
		BYTE Buffer[BUFSIZE];
		BYTE Des[TEXTSIZE];
		NumBytes = recv(Sock, Buffer, BUFSIZE - 1, 0);
		if(NumBytes < 0){
			perror("recv() failed\n");
			exit(1);
		}
		else if (NumBytes == 0){
			perror("connection closed prematurely");
		}
		Buffer[NumBytes] = '\0';
		fputs(Buffer, stdout);
		/// 전송 데이터 입력 부분 시작
		fputs("Insert : ", stdout);
		fgets(SendStr, sizeof(SendStr), stdin);
		SendStrLen = strlen(SendStr);
		SendStr[SendStrLen - 1] = '\0';
		//dataEncrypt(DeviceKey, SendStr, Des);			/**< 암호화 데이터 전송의 경우 이 코드의 주석을 제거 */
		//sendData(Sock, Des, strlen(Des));				/**< 암호화 데이터 전송의 경우 이 코드의 주석을 제거 */
		sendData(Sock, SendStr, SendStrLen);			/**<일반 데이터 전송 , 암호화 데이터 전송의 경우 주석처리  */
	}

	fputc('\n', stdout);

	close(Sock);

	exit(0);
}

/**
  *	@brief 입력 받은 데이터 전송
  *	@param	Sock socket 매개 변수
  * @param	*SendStr	송신할 데이터
  *	@param	SendStrLen	송신한 데이터 길이
  *	@return	전송된 데이터 길이
  */
size_t sendData(int Sock, BYTE *SendStr,  size_t SendStrLen){
	ssize_t NumBytes;
	BYTE SendData[BUFSIZE];
	SendData[0] = '\0';
	printf("%s\n", SendStr);

	sprintf(SendData, "{\'data\':\'%s\',\'value\':''}", SendStr);
	NumBytes = send(Sock, SendData, strlen(SendData), 0);
	puts(SendData);
	return NumBytes;
}

/**
  *	@brief	입력받은 데이터 암호화
  *	@param	*DeviceKey 	디바이스 인증 키
  *	@param	*Src		암호화 할 데이터
  *	@param	*Des		암호화 된 데이터 저장 공간
  */
size_t dataEncrypt(BYTE* DeviceKey, BYTE* Src, BYTE* Des){
	BYTE ekey[ENCRYPT_KEY_SIZE];										/**< 암호화키 저장 변수 */
	
	SOT_KeyGen(DeviceKey, strlen(DeviceKey), ekey, ENCRYPT_KEY_SIZE); 
	aes_encrypt(Des, Src, ekey, strlen(Src));	
	return strlen(Des);
}
