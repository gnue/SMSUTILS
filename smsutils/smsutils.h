/*------------------------------------------------------------------------*/
/**
 * @file	smsutils.h
 * @brief   Sudden Motion Sensor
 *
 * @author  M.Nukui
 * @date	2006-05-03
 *
 * Copyright (C) 2006 M.Nukui All rights reserved.
 */

/**
 * @page LICENSE ���C�Z���X
 * 
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

/**
 * @mainpage smsutils
 * 
 *	SMS�iSudden Motion Sensor Utilties:�ً}���[�V�����Z���T�j�𓋍ڂ��Ă��� MacBook, MacBook Pro, iBook G4, PowerBook G4
 *	�̂��߂̃��[�e�B���e�B
 *
 * @section FUNCTIONS �֐�
 *
 * - @ref smsOpen		SMS �� IOService ���I�[�v������
 * - @ref smsClose		SMS �� IOService ���N���[�Y����
 * - @ref smsGetData	SMS �̃f�[�^���擾
 *
 * @section STRUCTURES �\����
 *
 * - @ref sms_t			SMS�\����
 * - @ref sms_data_t	SMS�f�[�^�\����
 *
 * @section USAGE �g����
 *
 * - �w�b�_�t�@�C��	smsutils.h
 * - �v�����N			IOKit.framework
 *
 * @code
 *
 *	sms_data_t	data;
 *	sms_t		sms;
 *
 *	// SMS�T�[�r�X�̃I�[�v��
 *	if (smsOpen(&sms))
 *	{	// �G���[
 *		return -1;
 *	}
 *
 *	// �f�[�^�̎擾
 *	if (! smsGetData(&sms, &data))
 *	{	// sms.unit ���悸�邱�Ƃɂ��P�ʂ�x�ɕϊ����Ă��邱�Ƃɒ��Ӂi�@��ʂ̈Ⴂ���z�����Ă��܂��j
 *		printf("x = %f, y = %f, z = %f\n", data.x * sms.unit, data.z * sms.unit, data.z * sms.unit);
 *	}
 *
 *	// SMS�T�[�r�X�̃N���[�Y
 *	smsClose(&sms);
 *
 * @endcode
 *
 * @section LEGAL
 *
 * - @subpage LICENSE
 *
 * @note
 *
 * http://pallit.lhi.is/palli/dashlevel/ �� motion.c ���Q�l�ɂ����Ă��������܂����B
 * ������ MacBook Pro�� motion.c �̃f�[�^�\���͊Ԉ���Ă���̂Œ��Ӂi�������� x, y, z �e2byte�j
 *
 * �܂� SMS �̊T�v�� http://osxbook.com/book/bonus/chapter10/ams/ ���Q�l�ɂȂ�܂��B
 */


#ifndef	SMSUTILS_H
#define	SMSUTILS_H


/* �w�b�_�t�@�C�� */
#include <IOKit/IOKitLib.h>
#include <stdint.h>


/* �\���� */

/// SMS�T�[�r�X�̏��i�@�했�j
typedef struct {
	const char *	name;			///< �N���X��
	unsigned int	kernFunc;		///< ���\�b�h�̃C���f�b�N�X�ԍ�
	IOItemCount		inputSize;		///< Input �\���̂̃T�C�Y
	IOByteCount		outputSize;		///< Output �\���̂̃T�C�Y
	int				type;			///< �\���̂̎��
	int				maxValue;		///< �f�[�^�̍ő�l
} sms_service_t;


/// SMS�\����
typedef struct {
	io_connect_t	connect;		///< �ڑ����Ă���IO�T�[�r�X
	sms_service_t *	service;		///< SMS�T�[�r�X�̏��
	float			unit;			///< �P�ʁi�悶��Ɠx�ɕϊ��j
} sms_t;


/// SMS�f�[�^�\����
typedef struct {
	int		x;						///< X���̌X��
	int		y;						///< Y���̌X��
	int		z;						///< Z���̌X��
} sms_data_t;


/* �֐��v���g�^�C�v */

#ifdef __cplusplus
extern "C" {
#endif


kern_return_t smsOpen(sms_t * sms);
kern_return_t smsClose(sms_t * sms);
kern_return_t smsGetData(sms_t * sms, sms_data_t * data);


#ifdef __cplusplus
}
#endif


#endif /* SMSUTILS_H */
