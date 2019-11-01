//===================================================================================================================================
//�y3DSound.cpp�z
// [�쐬��]HAL����GP12A332 16 �� �F��
// [�쐬��]2019/10/29
// [�X�V��]2019/10/29
//===================================================================================================================================
#include "3DSound.h"
#include "Sound.h"
#include "ImguiManager.h"
#include "AbstractScene.h"
#include "Player.h"

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
S3DManager::S3DManager()
{
#if(_MSC_VER >= GAME_MSC_VER)
	//�~�b�h�|�C���g�{�C�X�̍쐬(P1)
	if (FAILED(SoundInterface::GetXAudio2Interface()->CreateSubmixVoice(
		&MidpointVoice[playerNS::PLAYER1],									//�T�u�~�b�N�X�{�C�X
		ENDPOINT_INPUT_CHANNEL,												//�`�����l����(����)
		ENDPOINT_SAMPLE_RATE,												//�T���v�����O���[�g(����)
		XAUDIO2_VOICE_USEFILTER,												//�t�B���^�[�@�\
		0,																	//�v���Z�X�X�e�[�W
		&SendList,															//���M���X�g(S3D)
		NULL)))																//�G�t�F�N�g�`�F�[��
	{
		return;
	}
	//�~�b�h�|�C���g�{�C�X�̍쐬(P2)
	if (FAILED(SoundInterface::GetXAudio2Interface()->CreateSubmixVoice(
		&MidpointVoice[playerNS::PLAYER2],									//�T�u�~�b�N�X�{�C�X
		ENDPOINT_INPUT_CHANNEL,												//�`�����l����(����)
		ENDPOINT_SAMPLE_RATE,												//�T���v�����O���[�g(����)
		XAUDIO2_VOICE_USEFILTER,												//�t�B���^�[�@�\
		0,																	//�v���Z�X�X�e�[�W
		&SendList,															//���M���X�g(S3D)
		NULL)))																//�G�t�F�N�g�`�F�[��
	{
		return;
	}

	//�~�b�h�|�C���g�{�C�X�ւ̑��M���X�g�̍쐬
	SendDescriptor[playerNS::PLAYER1] = { XAUDIO2_SEND_USEFILTER,MidpointVoice[playerNS::PLAYER1] };
	MidSendList[playerNS::PLAYER1] = { 1,&SendDescriptor[playerNS::PLAYER1] };
	SendDescriptor[playerNS::PLAYER2] = { XAUDIO2_SEND_USEFILTER,MidpointVoice[playerNS::PLAYER2] };
	MidSendList[playerNS::PLAYER2] = { 1,&SendDescriptor[playerNS::PLAYER2] };

	//�~�b�h�|�C���g�{�C�X�̏�����
	float p1Matrix[] = { 1.0f,1.0f,0.0f,0.0f };
	float p2Matrix[] = { 0.0f,0.0f,1.0f,1.0f };
	MidpointVoice[playerNS::PLAYER1]->SetOutputMatrix(EndpointVoice, ENDPOINT_INPUT_CHANNEL, ENDPOINT_INPUT_CHANNEL, p1Matrix);
	MidpointVoice[playerNS::PLAYER2]->SetOutputMatrix(EndpointVoice, ENDPOINT_INPUT_CHANNEL, ENDPOINT_INPUT_CHANNEL, p2Matrix);
#endif
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
S3DManager::~S3DManager()
{
#if(_MSC_VER >= GAME_MSC_VER)
	//�~�b�h�|�C���g�{�C�X
	uninitSoundStop();
	SAFE_DESTROY_VOICE(MidpointVoice[playerNS::PLAYER1])
	SAFE_DESTROY_VOICE(MidpointVoice[playerNS::PLAYER2])
#endif
}

//===================================================================================================================================
//�yImGUI�ւ̏o�́z
//===================================================================================================================================
#ifdef _DEBUG
void S3DManager::outputGUI(void)
{
#if(_MSC_VER >= GAME_MSC_VER)
	if (!ImGui::CollapsingHeader("S3DInformation"))
	{
		//�g�p���̃o�b�t�@��
		ImGui::Text("Number of buffers:%d", bufferMax);

		//�g�p���̃{�C�X��
		ImGui::Text("Number of voice:%d", soundParametersList->nodeNum - 1);

		for (int i = 0; i < soundParametersList->nodeNum - 1; i++)
		{
			//�T�E���h�̃p�����[�^�[
			SOUND_PARAMETERS *tmpSoundParameters = soundParametersList->getValue(i);

			//�o�b�t�@
			LIST_BUFFER *tmpBuffer = GetBuffer(
				tmpSoundParameters->playParameters.endpointVoiceId,
				tmpSoundParameters->playParameters.soundId,
				tmpSoundParameters->playParameters.loop);

			//�Đ��ʒu&���擾
			XAUDIO2_VOICE_STATE state = { 0 };
			tmpSoundParameters->SourceVoice->GetState(&state);
			long playPoint = (long)state.SamplesPlayed;
			while (playPoint >= (int)(tmpBuffer->wavFile.data.waveSize / sizeof(short) / tmpBuffer->wavFile.fmt.fmtChannel))
			{
				playPoint -= (int)(tmpBuffer->wavFile.data.waveSize / sizeof(short) / tmpBuffer->wavFile.fmt.fmtChannel);
			}

			if (tmpSoundParameters->isPlaying)		//�Đ����Ă���
			{
				//�{�C�XID
				ImGui::Text("Voice ID:%d", tmpSoundParameters->playParameters.voiceID);

				//�T�E���h��
				switch (scene)
				{
				case SceneList::SPLASH:
					break;
				case SceneList::TITLE:
					break;
				case SceneList::TUTORIAL:
					break;
				case SceneList::CREDIT:
					break;
				case SceneList::GAME:
					ImGui::Text("%s", gameS3DPathList[tmpSoundParameters->playParameters.soundId]);
					break;
				case SceneList::RESULT:
					break;
				case SceneList::NONE_SCENE:
					break;
				default:
					break;
				}

				//����
				float volume = 0.0f;
				tmpSoundParameters->SourceVoice->GetVolume(&volume);
				ImGui::Text("volume:%f", volume);

				//�g�`�̕`��
				int saveDataMax = 5512;	//�擾����f�[�^��
				int dataMax = (saveDataMax / tmpBuffer->wavFile.fmt.fmtChannel) + 2;	 //�Z�[�u�������f�[�^�̐�/�`�����l���� + 2
				float *fData = new (float[dataMax]);
				memset(fData, 0, sizeof(float)*dataMax);
				fData[0] = (float)SHRT_MIN;
				fData[dataMax - 1] = (float)SHRT_MAX;
				int wtPos = dataMax - 2;
				for (int j = saveDataMax - 1; j > 0; j -= tmpBuffer->wavFile.fmt.fmtChannel)
				{
					for (int k = 0; k < tmpBuffer->wavFile.fmt.fmtChannel; k++)
					{
						if (playPoint - j < 0)
						{
							fData[wtPos] = 0.0f;
							continue;
						}

						fData[wtPos] += ((float)tmpBuffer->wavFile.data.waveData[((playPoint - j) * tmpBuffer->wavFile.fmt.fmtChannel) - k] / (float)tmpBuffer->wavFile.fmt.fmtChannel);
					}
					wtPos--;
				}
				ImVec2 plotextent(ImGui::GetContentRegionAvailWidth(), 100);
				ImGui::PlotLines("", fData, dataMax, 0, "Sound wave", FLT_MAX, FLT_MAX, plotextent);
				SAFE_DELETE_ARRAY(fData);

				//�Đ��ʒu
				ImGui::ProgressBar(playPoint / (float)(tmpBuffer->wavFile.data.waveSize / sizeof(short) / tmpBuffer->wavFile.fmt.fmtChannel));

			}
		}
	}
#endif
}
#endif

//===================================================================================================================================
//�y�X�e�[�W�J�ڂɍ��킹�ĕK�v�ȃT�E���h�o�b�t�@��p�ӂ���z
//===================================================================================================================================
void S3DManager::SwitchAudioBuffer(int scene)
{
#if(_MSC_VER >= GAME_MSC_VER)
	//�T�E���h�f�B���N�g���ɐݒ肷��
	setSoundDirectory(ENDPOINT_VOICE_LIST::ENDPOINT_S3D);

#if _DEBUG
	//�V�[���̍X�V
	S3DManager::scene = scene;
#endif

	//�������
	for (int i = 0; i < S3DManager::bufferMax; i++)
	{
		SAFE_DELETE_ARRAY(S3DManager::bufferList[i].wavFile.data.waveData);
	}
	SAFE_DELETE_ARRAY(S3DManager::bufferList);

	switch (scene)
	{
	case SceneList::SPLASH:
		S3DManager::bufferList = new LIST_BUFFER[SPLASH_S3D_LIST::SPLASH_S3D_MAX];
		bufferMax = SPLASH_S3D_LIST::SPLASH_S3D_MAX;
		break;
	case SceneList::TITLE:
		S3DManager::bufferList = new LIST_BUFFER[TITLE_S3D_LIST::TITLE_S3D_MAX];
		bufferMax = TITLE_S3D_LIST::TITLE_S3D_MAX;
		break;
	case SceneList::TUTORIAL:
		break;
	case SceneList::CREDIT:
		break;
	case SceneList::GAME:
		S3DManager::bufferList = new LIST_BUFFER[GAME_S3D_LIST::GAME_S3D_MAX];
		for (int i = 0; i < GAME_S3D_LIST::GAME_S3D_MAX; i++)
		{
			S3DManager::bufferList[i].buffer = { 0 };

			FILE *fp = nullptr;
			fp = fopen(gameS3DPathList[i], "rb");
			S3DManager::bufferList[i].wavFile = LoadWavChunk(fp);

			S3DManager::bufferList[i].buffer.pAudioData = (BYTE*)S3DManager::bufferList[i].wavFile.data.waveData;
			S3DManager::bufferList[i].buffer.AudioBytes = S3DManager::bufferList[i].wavFile.data.waveSize;
			S3DManager::bufferList[i].buffer.Flags = XAUDIO2_END_OF_STREAM;

			fclose(fp);
		}
		bufferMax = GAME_S3D_LIST::GAME_S3D_MAX;
		break;
	case SceneList::RESULT:
		break;
	case SceneList::NONE_SCENE:
		break;
	case SceneList::CREATE:
		bufferMax = CREATE_S3D_LIST::CREATE_S3D_MAX;
		break;
	default:
		break;
	}
#endif
}

#if(_MSC_VER >= GAME_MSC_VER)
//===================================================================================================================================
//�y�\�[�X�{�C�X�̍쐬�z
//===================================================================================================================================
void S3DManager::MakeSourceVoice(PLAY_PARAMETERS *playParameters, LIST_BUFFER *listBuffer)
{
		//�g�`�̃t�H�[�}�b�g
		WAVEFORMATEX pcm;
		memset(&pcm, 0, sizeof(pcm));

		//�Đ��̃p�����[�^
		SOUND_PARAMETERS *tmpSoundParameters = soundParametersList->getValue(soundParametersList->nodeNum - 1);
		playParameters->voiceID = voiceIDCnt;
		tmpSoundParameters->playParameters = *playParameters;
		tmpSoundParameters->stopPoint = 0;
		tmpSoundParameters->isPlaying = false;
		tmpSoundParameters->isSpeed = false;

		//�Đ����x�̕ύX
		if (tmpSoundParameters->playParameters.speed != NULL)
		{
			//���true�ɂ���
			tmpSoundParameters->isSpeed = false;
		}

		//�g�`�̃t�H�[�}�b�g
		pcm.cbSize = 0;
		pcm.nChannels = listBuffer->wavFile.fmt.fmtChannel;
		pcm.wBitsPerSample = listBuffer->wavFile.fmt.fmtBitPerSample;
		pcm.nSamplesPerSec = listBuffer->wavFile.fmt.fmtSampleRate;
		pcm.wFormatTag = WAVE_FORMAT_PCM;
		pcm.nBlockAlign = (listBuffer->wavFile.fmt.fmtChannel*listBuffer->wavFile.fmt.fmtBitPerSample) / 8;
		pcm.nAvgBytesPerSec = listBuffer->wavFile.fmt.fmtSampleRate*pcm.nBlockAlign;

		//�\�[�X�{�C�X�̍쐬
		SoundInterface::GetXAudio2Interface()->CreateSourceVoice(
			&tmpSoundParameters->SourceVoice,
			&pcm,
			XAUDIO2_VOICE_USEFILTER,
			XAUDIO2_MAX_FREQ_RATIO,
			NULL,
			&MidSendList[tmpSoundParameters->playParameters.playerID],
			NULL);

		//�f�t�H�[���g�{�����[��
		tmpSoundParameters->SourceVoice->SetVolume(0.0f);

		//�o�b�t�@�̒�o
		tmpSoundParameters->SourceVoice->SubmitSourceBuffer(&listBuffer->buffer);

		//�m�[�h�̍X�V����
		soundParametersList->insertAfter(soundParametersList->getNode(soundParametersList->nodeNum - 1));
		soundParametersList->listUpdate();

		//�{�C�XID
		voiceIDCnt++;
		if (voiceIDCnt > LONG_MAX)
		{
			voiceIDCnt -= LONG_MAX;
		}

		//�Đ�
		playSound(playParameters);
}
#endif

#if(_MSC_VER >= GAME_MSC_VER)
//===================================================================================================================================
//�y�\�[�X�{�C�X�̍쐬�z
//===================================================================================================================================
void S3DManager::SetVolume(const PLAY_PARAMETERS playParameters, float volume)
{
	for (int i = 0; i < soundParametersList->nodeNum - 1; i++)
	{
		SOUND_PARAMETERS *tmpSoundParameters = soundParametersList->getValue(i);

		if (tmpSoundParameters->playParameters.voiceID == playParameters.voiceID)
		{
			//�{�����[��
			tmpSoundParameters->SourceVoice->SetVolume(volume);
		}
	}
}
#endif