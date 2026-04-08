#include <windows.h>   // Beep 所在头文件
#include <mmsystem.h>
#include <iostream>
#include <cmath>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//A4=440Hz, E、F和B、C之间是半音（1.05946倍），全音是1.122462倍 
double A4=440;
double G4=A4/1.122462;
double F4=G4/1.122462;
double E4=F4/1.05946;
double D4=E4/1.122462;
double C4=D4/1.122462;//中央C 
double B4=A4*1.122462;

double C5=B4*1.05946;

double B3=C4/1.05946;
double A3=B3/1.122462;
double G3=A3/1.122462;

void PlayTone(double frequency, float duration) {//产生良好正弦波的函数，由GPT提供 
//	std::cout<<"Playing: f="<<frequency<<"Hz, t="<<duration<<"ms"<<std::endl;
    int sampleRate = 44100;  // 采样率
    int numSamples = duration * sampleRate / 1000;  // 持续时间的采样点数
    short* waveData = new short[numSamples];

    // 直接使用 double 类型频率生成波形
    for (int i = 0; i < numSamples; i++) {
        // 计算每个采样点的弧度，使用 double 类型频率
        waveData[i] = static_cast<short>(32767 * sin(2 * 3.14159 * frequency * i / sampleRate));
    }

    // 配置WAVEFORMATEX结构
    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 16;
    wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
    wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

    HWAVEOUT hWaveOut;
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL);
//    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wf, 0, 0, 0);
    //编译时添加	-lwinmm
    //devc++可以在【项目→项目属性→参数→链接】中添加，针对当前项目 
	//或者【工具→编译选项→编译时加入以下命令】，全局生效 

    // 准备音频数据头
    WAVEHDR wh = {};
    wh.lpData = (LPSTR)waveData;
    wh.dwBufferLength = numSamples * sizeof(short);
    wh.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;

    waveOutPrepareHeader(hWaveOut, &wh, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &wh, sizeof(WAVEHDR));

    // 等待播放完成
    Sleep(duration);

    waveOutUnprepareHeader(hWaveOut, &wh, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    delete[] waveData;
}

void play_music(){
	PlayTone(C4,500);
	PlayTone(D4,500);
	PlayTone(E4,500);
	PlayTone(F4,500);
	PlayTone(G4,500);
	PlayTone(A4,500);
	PlayTone(B4,500);
	PlayTone(C5,500);
}

void play_DFH(float bias){
	double beat=1000;
	G3*=bias;
	A3*=bias;
	B3*=bias;
	C4*=bias;
	D4*=bias;
	E4*=bias;
	F4*=bias;
	G4*=bias;
	A4*=bias;
	B4*=bias;
	C5*=bias;
	
	std::cout<<"东";
	PlayTone(G4,beat);
	std::cout<<"方";
	PlayTone(G4,beat/2);
	PlayTone(A4,beat/2);
	std::cout<<"红，";
	PlayTone(D4,beat*2);
	std::cout<<"太";
	PlayTone(C4,beat);
	std::cout<<"阳";
	PlayTone(C4,beat/2);
	PlayTone(A3,beat/2);
	std::cout<<"升，"<<std::endl;
	PlayTone(D4,beat*2);
	std::cout<<"中";
	PlayTone(G4,beat);
	std::cout<<"国";
	PlayTone(G4,beat);
	std::cout<<"出";
	PlayTone(A4,beat/2);
	PlayTone(C5,beat/2);
	std::cout<<"了";
	PlayTone(A4,beat/2);
	std::cout<<"个";
	PlayTone(G4,beat/2);
	std::cout<<"毛";
	PlayTone(C4,beat);
	std::cout<<"泽";
	PlayTone(C4,beat/2);
	PlayTone(A3,beat/2);
	std::cout<<"东。"<<std::endl;
	PlayTone(D4,beat*2);
	std::cout<<"他";
	PlayTone(G4,beat);
	std::cout<<"为";
	PlayTone(D4,beat);
	std::cout<<"人";
	PlayTone(C4,beat);
	std::cout<<"民";
	PlayTone(B3,beat/2);
	PlayTone(A3,beat/2);
	std::cout<<"谋";
	PlayTone(G3,beat);
	std::cout<<"幸";
	PlayTone(G4,beat);
	std::cout<<"福，";
	PlayTone(D4,beat);
	std::cout<<"呼";
	PlayTone(E4,beat/2);
	std::cout<<"儿";
	PlayTone(D4,beat/2);
	std::cout<<"嘿";
	PlayTone(C4,beat);
	std::cout<<"哟，"<<std::endl;
	PlayTone(C4,beat/2);
	PlayTone(A3,beat/2);
	std::cout<<"他";
	PlayTone(D4,beat/2);
	std::cout<<"是";
	PlayTone(E4,beat/2);
	std::cout<<"人";
	PlayTone(D4,beat/2);
	std::cout<<"民";
	PlayTone(C4,beat/2);
	std::cout<<"大";
	PlayTone(D4,beat/2);
	PlayTone(C4,beat/2);
	std::cout<<"救";
	PlayTone(B3,beat/2);
	PlayTone(A3,beat/2);
	std::cout<<"星";
	PlayTone(G3,beat*4);
}

int main(int argc, char** argv) {
//	std::cout<<"execute successful"<<std::endl;
	play_DFH(2);
//	std::cout<<"一个八度相差"<<(C5/C4)<<"倍"<<std::endl;//2倍 
	return 0;
}
