#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"
#include <stdio.h>

#define BUFFER_SIZE 5  // 이동 평균 필터를 위한 버퍼 크기

unsigned int DFC = 1; // DeFaultColor, 1이 흰색이고 0이 검은색
unsigned int MODE = 1;
unsigned int count50ms = 0; // 작동시간
int sec;
int cnt = 0;


// 각 센서 채널에 대해 최근 ADC 값을 저장할 배열
unsigned int IRBuffers[6][BUFFER_SIZE] = {{0}};
unsigned int IRTemp[6] = {0};
unsigned int sidePSD = 0;
unsigned int frontPSD = 0;
unsigned int PSDBuffers[2][3] = {{0}};

int enablePSD = 0;

// 최솟값 및 최댓값 배열
unsigned int IRmin[6] = {1024, 1024, 1024, 1024, 1024, 1024};
unsigned int IRmax[6] = {0, 0, 0, 0, 0, 0};


unsigned int motorstatus = 1; // 1전진 2후진 3좌회전 4우회전
unsigned int bit = 0x00; // LED 인식에 사용할 비트들

// 이동 평균 필터 함수
unsigned int ADCFilter(unsigned int channel) {
	unsigned long sum = 0;
	for (unsigned int i = 0; i < BUFFER_SIZE; i++) {
		sum += IRBuffers[channel][i];
	}
	return (unsigned int)(sum / BUFFER_SIZE);
}

unsigned int PSDFilter(unsigned int channel) {
	unsigned long sum = 0;
	for (unsigned int i = 0; i < 3; i++) {
		sum += PSDBuffers[channel][i];
	}
	return (unsigned int)(sum / 3);
}

int readSidePSD(void){
	unsigned int SPSDsensor;
	
	ADMUX = 0x47; // ADC 채널 선택
	ADCSRA |= 0x40; // ADC 변환 시작
	while ((ADCSRA & 0x10) == 0); // 변환 완료 대기
	ADCSRA |= 0x10; // ADIF 플래그 클리어
	
	PSDBuffers[0][1] = ADC;

	SPSDsensor = PSDFilter(0)*100/700;//얘는 700까지 올라가는 반면
	//PSD값 받기, 거리 범위에 따라 값 받기
	
	//PSDsensor값 13 정도를 기준으로 10에서 16까지를 안정권으로 잡자
	return SPSDsensor;

}

int readFrontPSD(void){
	unsigned int FPSDsensor;
	
	ADMUX = 0x40; // ADC 채널 선택
	ADCSRA |= 0x40; // ADC 변환 시작
	while ((ADCSRA & 0x10) == 0); // 변환 완료 대기
	ADCSRA |= 0x10; // ADIF 플래그 클리어
		
	PSDBuffers[1][1] = ADC;
	
	FPSDsensor = PSDFilter(1)*100/205;//얘는 205 정도까지밖에 안올라감
	//PSD값 받기, 거리 범위에 따라 값 받기
	//PSDsensor값 13 정도를 기준으로 10에서 16까지를 안정권으로 잡자
	return FPSDsensor;

}

unsigned int utillizePSD(int channel){//측면 쓸거면 채널0, 전방 쓸거면 채널1
		//여기에 PSD값 입력- PSD값 범위로 나누기
		if (channel == 0){
			sidePSD = readSidePSD();
			lcdNumber(0, 11, sidePSD);
			return sidePSD;
		}else if(channel == 1){
			frontPSD = readFrontPSD();
			lcdNumber(0, 14, frontPSD);
			return frontPSD;
		}else{
		lcdNumber(0, 11, 00);
		lcdNumber(0, 14, 00);
		return 0;
		}
}

int MODE1(unsigned int IRbit){
	unsigned int CENTER = ((1 << (4 - 1 + 1)) - 1) << 1; // 가운데 4개 비트
	unsigned int RIGHT = ((1 << (2 - 0 + 1)) - 1) << 0; // 우측 3개 비트
	unsigned int LEFT = ((1 << (5 - 3 + 1)) - 1) << 3; // 좌측 3개 비트
	
	
	if ((((IRbit & CENTER) == (0b0100 << 1) ||
	(IRbit & CENTER) == (0b0010 << 1) || (IRbit & CENTER) == (0b0110 << 1) || (IRbit & CENTER) == (0b0000 << 1)
	|| (IRbit & CENTER) == (0b0100 << 1)|| (IRbit & CENTER) == (0b0111 << 1)|| (IRbit & CENTER) == (0b1110 << 1))
	&& !(IRbit & (1 << 5)) && !(IRbit & (1 << 0)))) {
		//반전색 선 인식
			if(sec > 12){
				MODE = 2;
				lcdClear();
				lcdString(0, 0, "time:");
				lcdString(1, 0, "motor:");
				lcdString(1, 9 ,"MODE: ");
				sec = 0;
				return 0;
				}else{
				return 0;
			}	
	} else if (((IRbit & CENTER) == (0b1011 << 1) ||  
	(IRbit & CENTER) == (0b1101 << 1) || (IRbit & CENTER) == (0b0000 << 1) ||
	(IRbit & CENTER) == (0b1001 << 1) || (IRbit & CENTER) == (0b1100 << 1) ||
	(IRbit & CENTER) == (0b0011 << 1) || (IRbit & CENTER) == (0b0001 << 1) ||
	(IRbit & CENTER) == (0b1000 << 1)) && (IRbit & (1 << 5)) && (IRbit & (1 << 0))) {
		// 가운데 줄 인식 - 직진
		return 1;

		
	} else if (((IRbit & LEFT) == (0b011 << 3) || (IRbit & LEFT) == (0b001 << 3) || (IRbit & LEFT) == (0b000 << 3)
	|| (IRbit & LEFT) == (0b101 << 3)) && (IRbit & (1 << 0))) {  
		// 좌측 3개 비트
		return 3;


	} else if ((((IRbit & RIGHT) == (0b110 << 0) || (IRbit & RIGHT) == (0b100 << 0) || (IRbit & RIGHT) == (0b000 << 0))
|| (IRbit & RIGHT) == (0b001 << 0) || (IRbit & RIGHT) == (0b101 << 0)) && (IRbit & (1 << 5))) {
		//우측 3개 비트
		return 4;

} else if ((IRbit) == 0b111111) {
	// 아무것도 인식 못할 때: 우회전(1구간 바코드전)
		if(sec > 14){
			MODE = 2;
			lcdClear();
			lcdString(0, 0, "time:");
			lcdString(1, 0, "motor:");
			lcdString(1, 9 ,"MODE: ");
			sec = 0;
			return 4;
			}else{
			return 4;
		}	
	}
	return 2; // 기본값 (에러)
}


int MODE2(unsigned int IRbit){
	unsigned int CENTER = ((1 << (4 - 1 + 1)) - 1) << 1; // 가운데 4개 비트
	unsigned int RIGHT = ((1 << (2 - 0 + 1)) - 1) << 0; // 우측 3개 비트
	unsigned int LEFT = ((1 << (5 - 3 + 1)) - 1) << 3; // 좌측 3개 비트
	
	
	if ((((IRbit & CENTER) == (0b0100 << 1) ||
	(IRbit & CENTER) == (0b0010 << 1) || (IRbit & CENTER) == (0b0110 << 1) || (IRbit & CENTER) == (0b0000 << 1)
	|| (IRbit & CENTER) == (0b0100 << 1)|| (IRbit & CENTER) == (0b0111 << 1)|| (IRbit & CENTER) == (0b1110 << 1))
	&& !(IRbit & (1 << 5)) && !(IRbit & (1 << 0)))) {
		//반전색 선 인식
		if (IRbit == 0b000000) {//반전 구간 진입시 정규화를 다시 하지 않으면 흰 테이프를 인식못함
			if (cnt >= 20) {//일정 시간 동안 반전 구간에 머무르면
				MODE = 3;
				lcdClear();
				lcdString(0, 0, "time:");
				lcdString(1, 0, "motor:");
				lcdString(1, 9, "MODE: ");
				sec = 0;
				DFC = 0;
				cnt = 0;
				enablePSD = 1;
				for (int i = 0; i < 6; i++) {//정규화 배열 초기화
					IRmin[i] = 1024;
					IRmax[i] = 0;
				}
			}
			else {//cnt가 덜 찼으면
				if (sec > 2) {
					cnt++;
					return 1;
				}
			}
		}
		cnt = 0;
		return 0;
		
	} else if (((IRbit & CENTER) == (0b1011 << 1) ||
	(IRbit & CENTER) == (0b1101 << 1) || (IRbit & CENTER) == (0b0000 << 1) ||
	(IRbit & CENTER) == (0b1001 << 1) || (IRbit & CENTER) == (0b1100 << 1) ||
	(IRbit & CENTER) == (0b0011 << 1) || (IRbit & CENTER) == (0b0001 << 1) ||
	(IRbit & CENTER) == (0b1000 << 1)) && (IRbit & (1 << 5)) && (IRbit & (1 << 0))) {
		// 가운데 줄 인식 - 직진
		return 1;
		
	} else if (((IRbit & LEFT) == (0b011 << 3) || (IRbit & LEFT) == (0b001 << 3) || (IRbit & LEFT) == (0b000 << 3)
	|| (IRbit & LEFT) == (0b101 << 3)) && (IRbit & (1 << 0))) {
		// 좌측 3개 비트
		cnt = 0;
		return 5;

	} else if ((((IRbit & RIGHT) == (0b110 << 0) || (IRbit & RIGHT) == (0b100 << 0) || (IRbit & RIGHT) == (0b000 << 0))
	|| (IRbit & RIGHT) == (0b001 << 0) || (IRbit & RIGHT) == (0b101 << 0)) && (IRbit & (1 << 5))) {
		//우측 3개 비트
		cnt = 0;
		return 6;

		} else if ((IRbit) == 0b111111) {
		return 2;
	}
	return 2; // 기본값 (에러)
}

int MODE3(unsigned int IRbit){
	unsigned int CENTER = ((1 << (4 - 1 + 1)) - 1) << 1; // 가운데 4개 비트
	unsigned int RIGHT = ((1 << (2 - 0 + 1)) - 1) << 0; // 우측 3개 비트
	unsigned int LEFT = ((1 << (5 - 3 + 1)) - 1) << 3; // 좌측 3개 비트
	
	
	if ((((IRbit & CENTER) == (0b0100 << 1) ||
	(IRbit & CENTER) == (0b0010 << 1) || (IRbit & CENTER) == (0b0110 << 1) || (IRbit & CENTER) == (0b0000 << 1)
	|| (IRbit & CENTER) == (0b0100 << 1)|| (IRbit & CENTER) == (0b0111 << 1)|| (IRbit & CENTER) == (0b1110 << 1))
	&& !(IRbit & (1 << 5)) && !(IRbit & (1 << 0)))) {
		//반전색 선 인식
		if ((IRbit & CENTER) == (0b0000 << 1)) {//3구간 벽 시작과 끝, 차단기 앞 흰 선
			if (enablePSD == 0 && sec >= 1) {
				enablePSD = 1;
				utillizePSD(0);
				utillizePSD(1);
				return 0;
			}
			else if (enablePSD == 1) {
				if (sec > 4 && sec <= 6) {//차단기 기다리기
					return 9;
				}else if (sec > 6){
					if (utillizePSD(1) >= 40) {//차단기에 너무 가까이 있으면
						return 2;
					}
					else if (utillizePSD(1) < 40 && utillizePSD(1) >= 29) {//차단기 올라가는거 기다리기
						return 9;
					}
					else if (utillizePSD(1) < 29) {//차단기 올라가면
						return 0;
					}
				}
				else {
					return 1;//차단기가 없는 구간에서는 직진
				}

			}
			else {//2구간 처음 진입 시
				return 2;
			}

		}
		else {
			return 1;
		}
		
	} else if (((IRbit & CENTER) == (0b1011 << 1) ||
	(IRbit & CENTER) == (0b1101 << 1) || (IRbit & CENTER) == (0b0000 << 1) ||
	(IRbit & CENTER) == (0b1001 << 1) || (IRbit & CENTER) == (0b1100 << 1) ||
	(IRbit & CENTER) == (0b0011 << 1) || (IRbit & CENTER) == (0b0001 << 1) ||
	(IRbit & CENTER) == (0b1000 << 1)) && (IRbit & (1 << 5)) && (IRbit & (1 << 0))) {
		// 가운데 줄 인식 - 직진
		
		if(enablePSD == 1  && utillizePSD(1) > 40){
			return 2;
		}else{
			return 1;
		}
	} else if (((IRbit & LEFT) == (0b011 << 3) || (IRbit & LEFT) == (0b001 << 3) || (IRbit & LEFT) == (0b000 << 3)
	|| (IRbit & LEFT) == (0b101 << 3)) && (IRbit & (1 << 0))) {
		// 좌측 3개 비트
		return 1;

	} else if ((((IRbit & RIGHT) == (0b110 << 0) || (IRbit & RIGHT) == (0b100 << 0) || (IRbit & RIGHT) == (0b000 << 0))
	|| (IRbit & RIGHT) == (0b001 << 0) || (IRbit & RIGHT) == (0b101 << 0)) && (IRbit & (1 << 5))) {
		//우측 3개 비트
		return 4;
		if(sec > 15){//주차장 탈출 도중 ㅏ자 모양 만나면
				MODE = 4;
				lcdClear();
				lcdString(0, 0, "time:");
				lcdString(1, 0, "motor:");
				lcdString(1, 9, "MODE: ");
				sec = 0;
				cnt = 0;
				return 41;
		}

		} else if ((IRbit) == 0b111111) {
		// 아무것도 인식 못할 때
		if (enablePSD == 1) {
			utillizePSD(0);
			utillizePSD(1);
			if (sec < 9) {//벽타기
				if (utillizePSD(0) > 21) {//가까우면
					return 7;
				}
				else if (utillizePSD(0) <= 21 && utillizePSD(0) >= 16) {//적당하면
					return 1;
				}
				else if (utillizePSD(0) < 16 && utillizePSD(0) > 10) {//멀면
					return 8;
				}
				else {
					return 5;//예외 처리
				}
			}
			else {
				if (sec > 9) {//주차 -> 회전 시간 맞춰야함
					if (utillizePSD(1) >= 29) {
						PORTB = (PORTB & 0xF0) | 0x00;
						OCR1A = ICR1 * 0.0;
						OCR1B = ICR1 * 0.0;
						_delay_ms(5000);
						PORTB = (PORTB & 0xF0) | 0x06;
						OCR1A = ICR1 * 0.4;
						OCR1B = ICR1 * 0.4;
						_delay_ms(1000);
						return 1;
					}
					else if (utillizePSD(1) < 29) {
						return 1;
					}
					else {
						return 1;
					}
				}
			}
		}
		else if (sec <= 1) {//PSD 꺼졌을때(2구간 처음 진입할때)
			return 8;
		}
		return 5;
	}
	return 2; // 기본값 (에러)
}

int MODE4(unsigned int IRbit){
	unsigned int CENTER = ((1 << (4 - 1 + 1)) - 1) << 1; // 가운데 4개 비트
	unsigned int RIGHT = ((1 << (2 - 0 + 1)) - 1) << 0; // 우측 3개 비트
	unsigned int LEFT = ((1 << (5 - 3 + 1)) - 1) << 3; // 좌측 3개 비트
	//ㅓ, ㅏ, ㅜ 모양에서 회전을 해야 하기 때문에 우회전 조건과 좌회전 조건을 높은 우선순위에 둠
	
 if (((IRbit & LEFT) == (0b011 << 3) || (IRbit & LEFT) == (0b001 << 3) || (IRbit & LEFT) == (0b000 << 3)
|| (IRbit & LEFT) == (0b101 << 3)) && (IRbit & (1 << 0))) {
	// 좌측 3개 비트
	return 31;

} else if ((((IRbit & RIGHT) == (0b110 << 0) || (IRbit & RIGHT) == (0b100 << 0) || (IRbit & RIGHT) == (0b000 << 0))
|| (IRbit & RIGHT) == (0b001 << 0) || (IRbit & RIGHT) == (0b101 << 0)) && (IRbit & (1 << 5))) {
	//우측 3개 비트
	return 41;
	
	}else if ((((IRbit & CENTER) == (0b0100 << 1) ||
	(IRbit & CENTER) == (0b0010 << 1) || (IRbit & CENTER) == (0b0110 << 1) || (IRbit & CENTER) == (0b0000 << 1)
	|| (IRbit & CENTER) == (0b0100 << 1)|| (IRbit & CENTER) == (0b0111 << 1)|| (IRbit & CENTER) == (0b1110 << 1))
	&& !(IRbit & (1 << 5)) && !(IRbit & (1 << 0)))) {
		//반전색 선 인식
		//가로줄 인식->일단정지 후 차단기 올라가면 전진
		//가운데 이상한 거 껴있으면 후진
		if((IRbit & CENTER) == (0b0000 << 1) && sec < 3 && enablePSD == 1){
			if(utillizePSD(1) > 30){
				return 9;
			}else if(utillizePSD(1) <= 30){
				return 1;
			}
		}else if((IRbit & CENTER) == (0b0000 << 1) && sec >=3){
			return 1;
		}else{
			return 2;
		}
	} else if (((IRbit & CENTER) == (0b1011 << 1) ||
	(IRbit & CENTER) == (0b1101 << 1) || (IRbit & CENTER) == (0b0000 << 1) ||
	(IRbit & CENTER) == (0b1001 << 1) || (IRbit & CENTER) == (0b1100 << 1) ||
	(IRbit & CENTER) == (0b0011 << 1) || (IRbit & CENTER) == (0b0001 << 1) ||
	(IRbit & CENTER) == (0b1000 << 1)) && (IRbit & (1 << 5)) && (IRbit & (1 << 0))) {
		// 가운데 줄 인식 - 직진
		return 1;
		
	} else if ((IRbit) == 0b111111) {
		// 아무것도 인식 못할 때
		//T자 구간 유턴
			return 42;
	}
	return 2; // 기본값 (에러)
}


//맨 왼쪽 센서가 5번임, 선이 있는 곳이 0(LED 꺼짐)
int lineTrace(unsigned int IRbit) {
	if (MODE == 1){
		motorstatus = MODE1(IRbit);
	}else if(MODE == 2){
		motorstatus = MODE2(IRbit);
	}else if(MODE == 3){
		motorstatus = MODE3(IRbit);
	}else if(MODE == 4){
		motorstatus = MODE4(IRbit);
	}
	return 0;
}

// 센서 데이터 읽기 및 필터링
void readIRAndFilter(void) {
	unsigned int sensor = 0;
	unsigned int sensorNormal = 0;

	PORTA = 0xFF; // 모든 LED 끄기
	bit = 0; // 비트 초기화

	for (unsigned int i = 0; i < 6; i++) {
		ADMUX = 0x41 + i; // ADC 채널 선택
		ADCSRA |= 0x40; // ADC 변환 시작
		while ((ADCSRA & 0x10) == 0); // 변환 완료 대기
		ADCSRA |= 0x10; // ADIF 플래그 클리어

		// 현재 ADC 값을 버퍼에 저장
		IRBuffers[i][IRTemp[i]] = ADC;
		IRTemp[i] = (IRTemp[i] + 1) % BUFFER_SIZE;

		// 필터링된 ADC 값을 계산
		sensor = ADCFilter(i);

		if (sensor < IRmin[i]) {
			IRmin[i] = sensor;
		}
		if (sensor > IRmax[i]) {
			IRmax[i] = sensor;
		}

		// 정규화된 값 계산
		if (IRmax[i] != IRmin[i]) {
			sensorNormal = (sensor - IRmin[i]) * 100 / (IRmax[i] - IRmin[i]);
			} else {
			sensorNormal = 0; // 최댓값과 최솟값이 동일할 경우 0으로 설정
		}

		// 정규화된 값을 0~1 범위로 변환
		float sensorFinal = sensorNormal / 100.0;
	if (DFC == 1){
		if (sensorFinal >= 0.5) {
			bit |= (1 << i); // 비트 설정
			PORTA &= ~(1 << (i + 1)); // 해당 LED만 켜기
		}else{
			bit &= ~(1 << i); // 비트 설정
			PORTA |= (1 << (i + 1)); // 해당 LED만 끄기
			}
	}else{
		if (sensorFinal < 0.5) {//배경색이 검은색
			bit |= (1 << i); // 비트 설정
			PORTA &= ~(1 << (i + 1)); // 해당 LED만 켜기
		}else{
			bit &= ~(1 << i); // 비트 설정
			PORTA |= (1 << (i + 1)); // 해당 LED만 끄기
			}
		}
	}
}

// LCD 업데이트
void updateLCD(void) {
	lcdNumber(0, 6, sec);
	lcdNumber(1, 7, motorstatus);
	if(enablePSD == 0){
		lcdString(0, 10, "x");
		}else if(enablePSD == 1){
		lcdString(0, 10, "o");
	}
	lcdNumber(1, 14, MODE);
}


// 모터 제어
void controlMotors(void) {
	if (motorstatus == 1) { // 전진
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.3;
		OCR1B = ICR1 * 0.3;
		} else if (motorstatus == 2) { // 후진
		PORTB = (PORTB & 0xF0) | 0x0A;
		OCR1A = ICR1 * 0.1;
		OCR1B = ICR1 * 0.1;
		} else if (motorstatus == 3) { // 좌회전
		PORTB = (PORTB & 0xF0) | 0x06;
		OCR1A = ICR1 * 0.1;
		OCR1B = ICR1 * 0.5;
		} else if (motorstatus == 3) { // 제자리 좌회전 90도-아다리 맞춰놓기!!!
		PORTB = (PORTB & 0xF0) | 0x06;
		OCR1A = ICR1 * 0.4;
		OCR1B = ICR1 * 0.4;
		_delay_ms(500);
		} else if (motorstatus == 4) { // 우회전
		PORTB = (PORTB & 0xF0) | 0x09;
		OCR1A = ICR1 * 0.5;
		OCR1B = ICR1 * 0.1;
		} else if (motorstatus == 41) { // 제자리 우회전 90도-아다리 맞춰놓기!!!
		PORTB = (PORTB & 0xF0) | 0x09;
		OCR1A = ICR1 * 0.4;
		OCR1B = ICR1 * 0.4;
		_delay_ms(500);
		} else if (motorstatus == 42) { // 제자리 우회전 180도-아다리 맞춰놓기!!!
		PORTB = (PORTB & 0xF0) | 0x09;
		OCR1A = ICR1 * 0.4;
		OCR1B = ICR1 * 0.4;
		_delay_ms(1000);
		}else if (motorstatus == 5){ // 좌회전-고정
		PORTB = (PORTB & 0xF0) | 0x04;
		OCR1A = 0;
		OCR1B = ICR1 * 0.4;
		}else if (motorstatus == 6){ // 우회전-고정
		PORTB = (PORTB & 0xF0) | 0x01;
		OCR1A = ICR1 * 0.5;
		OCR1B = 0;
		}else if (motorstatus == 7){ //좌회전-전진(0x05로 할 시 오른쪽 모터 출력이 너무 강력해 듀티비 조절로 차이가 메꿔지지 않음)
		PORTB = (PORTB & 0xF0) | 0x04;
		OCR1A = 0;
		OCR1B = ICR1 * 0.4;
		_delay_ms(50);
		/*PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.3;
		OCR1B = ICR1 * 0.3;*/
		}else if (motorstatus == 8){ //우회전-전진
		PORTB = (PORTB & 0xF0) | 0x01;
		OCR1A = ICR1 * 0.4;
		OCR1B = 0;
		_delay_ms(50);
		/*PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.3;
		OCR1B = ICR1 * 0.3;*/
		}else if (motorstatus == 9){ //정지
		PORTB = (PORTB & 0xF0) | 0x00;
		OCR1A = ICR1 * 0.0;
		OCR1B = ICR1 * 0.0;
		_delay_ms(100);
		} else if (motorstatus == 0){ // 강제직진
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.5;
		OCR1B = ICR1 * 0.5;
		_delay_ms(210);
		}
}

int main(void) {
	// F 입력, B 모터, A LED
	DDRF = 0x00;
	DDRB = 0x6F;
	DDRA = 0xFF;

	EIMSK = 0b00001111; 
	EICRA = 0b11111111; // 상승엣지에 트리거

	TCNT0 = 231; // 타이머 초기화
	TCCR0 = 0x03; // 분주비 32
	TIMSK = 0x01; // 오버플로우 인터럽트 활성화

	ADMUX = 0x40;
	ADCSRA = 0x87;

	TCCR1A = 0xA2;
	TCCR1B = 0x1A;//prescaler 8
	TCCR1C = 0x00;

	ICR1 = 399;
	TCNT1 = 0x00;

	SREG = 0x80;
	sei();

	lcdInit();
	lcdClear();
	lcdString(0, 0, "time:");
	lcdString(1, 0, "motor:");
	lcdString(1, 9 ,"MODE: ");
	
	while (1) {
		readIRAndFilter();
		lineTrace(bit);	
		updateLCD();
		controlMotors();
	}
}



ISR(TIMER0_OVF_vect) {
	count50ms++;
	if(count50ms)
	if (count50ms >= 2000) {
		count50ms = 0;
		sec++;
	}
}

ISR(INT0_vect){//모드3 바로 진입
	MODE = 3;
	lcdClear();
	lcdString(0, 0, "time:");
	lcdString(1, 0, "motor:");
	lcdString(1, 9 ,"MODE: ");
	sec = 0;
	DFC = 0;
	cnt = 0;
	enablePSD = 0;
	for(int i = 0; i < 6; i++){//정규화 배열 초기화
		IRmin[i] = 1024;
		IRmax[i] = 0;
	}
}

ISR(INT1_vect){
	sec = 0;
	
}

ISR(INT2_vect){//모드4 바로 진입
	MODE = 4;
	lcdClear();
	lcdString(0, 0, "time:");
	lcdString(1, 0, "motor:");
	lcdString(1, 9 ,"MODE: ");
	sec = 0;
	DFC = 0;
	cnt = 0;
	enablePSD = 1;
	for(int i = 0; i < 6; i++){//정규화 배열 초기화
		IRmin[i] = 1024;
		IRmax[i] = 0;
	}
}	