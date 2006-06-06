/*------------------------------------------------------------------------*/
/**
 * @file	MyObject.m
 * @brief   SMS(Sudden Motion Sensor) �����I�Ƀ`�F�b�N���ĉ摜�̌X�����X�V����
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

#import "MyObject.h"

@implementation MyObject


- (void)timerSmsRotation:(NSTimer *)aTimer
{
	if (view)
	{	// view �����݂����
		sms_data_t	data;

		// SMS�f�[�^�̎擾
		if (! smsGetData(&sms, &data))
		{	// �摜�� X���̌X���Ɣ��Ε����ɉ�]�i���������ێ��j
			[view setBoundsRotation: - data.x * sms.unit];
			[view setNeedsDisplay: YES];
		}

	}
}

- (void)awakeFromNib
{
	// SMS�T�[�r�X���I�[�v������
	if (smsOpen(&sms))
	{	// �I�[�v���Ɏ��s�iSMS���g���Ȃ��j
		NSAlert *	alert = [NSAlert alertWithMessageText:@"smsOpen" 
											defaultButton:@"OK"
										  alternateButton:nil 
											  otherButton:nil
								informativeTextWithFormat:@"Don't open SMS IOService !"];

		[alert runModal];
		return;
	}

	// 0.1 �b�Ԋu�� SMS �̃`�F�b�N���s��
	[NSTimer scheduledTimerWithTimeInterval:0.1
									target:self
								  selector:@selector(timerSmsRotation:)
								  userInfo:nil
								   repeats:YES];
}

- (void)dealloc
{
	// SMS�T�[�r�X���N���[�Y����
	smsClose(&sms);
    [super dealloc];
}

@end
