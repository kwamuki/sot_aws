/**
  *	@file		sot_key_gen.h
  *	@brief		SoT crypto key generation header
  *	@author		James
  *	@date		2016.02.22
  *
  *	SoT crypto 프로젝트 소스 파일
  */
#ifndef		_SOT_KEY_GEN_H_
#define		_SOT_KEY_GEN_H_

#include "sot_key.h"
#include <time.h>
#include <stdlib.h>

/// DeviceKey 정보를 가지고 EncryptKey 를 생성함
void SOT_KeyGen(
		BYTE 	*DeviceKey,
		DWORD	DeviceKeyLen,
		BYTE	*EncryptKey,
		BYTE	EncryptKeyLen
		);

#endif
