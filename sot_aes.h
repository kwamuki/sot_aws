/**
  *	@file		sot_aes.h
  *	@brief		aes encrypt header file
  *	@author		James
  * @date		2014.05.07
  *
  *	SoT crypto 프로젝트 소스파일
  */
#ifndef	_SOTIS_AES_H
#define	_SOTIS_AES_H
#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>
#include <errno.h>
#include <string.h>

#define BLOCKSIZE	16		/**<  표준 블럭 사이즈 */

typedef unsigned char	BYTE;		/**< BYTE (unsigned char)형 선언 */

/**
  *	@brief	sot_aes 암호화 함수 
  *	@param	*cipherText 암호화 된 문자열을 저장할 포인터
  *	@param	*plainText 암호화 할 문자열
  *	@param	*key	암호화용 키 16자리
  *	@param	size	plainText 길이 
  *
  * SoT crypto 프로젝트 파일입니다. 
  */
int	aes_encrypt(BYTE* cipherText, BYTE* plainText, BYTE* key, size_t size);
/**
  *	@brief	sot_aes 복호화 함수 
  *	@param	*decryptedText 복호화 한 문자열 포인터
  *	@param	*cipherText	복호화 할 문자열
  *	@param	*key	암호화용 키 16자리
  *	@param	size	plainText 길이 
  *
  * SoT crypto 프로젝트 파일입니다. 
  */
int	aes_decrypt(BYTE* decryptedText, BYTE* cipherText, BYTE* key, size_t size);

#endif
