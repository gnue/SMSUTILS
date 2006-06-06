/*------------------------------------------------------------------------*/
/**
 * @file	getsms.c
 * @brief   SMS(Sudden Motion Sensor) コマンドライン・ツール
 *
 * @author  M.Nukui
 * @date	2006-05-03
 *
 * Copyright (C) 2006 M.Nukui All rights reserved.
 */

/*
 * ===== LICENSE =====
 * 
 * Copyright 2006 Makoto Nukui. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 * 
 *   1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *   and the following disclaimer.
 * 
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *   conditions and the following disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "smsutils.h"


int main(int argc,char *argv[])
{
	sms_data_t	data;
	sms_t		sms;

	// SMSサービスのオープン
	if (smsOpen(&sms))
		return EXIT_FAILURE;

	if (1 < argc)
	{	// 引数に ループ間隔があればループする
		useconds_t		usecs;

		// ループ間隔をマイクロ秒に変換
		usecs = atof(argv[1]) * 1000000.0;

		for (;;)
		{
			// SMSデータの取得
			if (smsGetData(&sms, &data)) break;

			printf("%d %d %d\n", data.x, data.y, data.z);
			usleep(usecs);
		}
	}
	else
	{
		if (! smsGetData(&sms, &data))
			printf("%d %d %d\n", data.x, data.y, data.z);
	}

	// SMSサービスのクローズ
	smsClose(&sms);

	return EXIT_SUCCESS;
}
