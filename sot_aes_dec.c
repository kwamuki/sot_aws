/**
  * @file		sot_aes_des.c
  * @brief		복화화 함수가 들어있는 파일
  * @author		James
  * @date		2016.02.20
  *
  * 리눅스에서 표준으로 지원 되는 libgcrypt 라이브러리중 AES 128 암호화 라이브러리를 사용하는 샘플 암호화 기능으로 
  * 사용자가 원하면 다른 암호화 라이브러리를 사용가능(사용자화, 커스터마이징)하나 서버에서 표준으로 지원 하는 함수입니다.
  */ 
#include "sot_aes.h"

typedef unsigned char	BYTE;		/**< BYTE (unsigned char) 형 선언 */

/**
  *	@brief	sotis_aes 복호화 파일
  *	@param	*decryptedText 복호화 한 문자열
  *	@param	*cipherText 복호화 할 문자열
  *	@param	*key	암호화용 키 16자리
  *	@param	size	plainText 길이 
  *
  * SoT crypto 프로젝트 파일입니다. 
  */
int	aes_decrypt(BYTE* decryptedText, BYTE* cipherText, BYTE* key, size_t size)
{
	gcry_error_t		err;
	gcry_cipher_hd_t	hd;			// 디스크립터

	if((err = gcry_cipher_open(&hd, GCRY_CIPHER_AES, GCRY_CIPHER_MODE_CFB, 0)) < 0){
		return;
	}

	if((err = gcry_cipher_setkey(hd, key, BLOCKSIZE)) < 0){
		return;
	}

	if((err = gcry_cipher_setiv(hd, key, BLOCKSIZE)) < 0){
		return;
	}

	if((err = gcry_cipher_decrypt(hd, decryptedText, size, cipherText, size)) < 0){
		return;
	}

	gcry_cipher_close(hd);
	
	return 0;
}
