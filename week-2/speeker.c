#include <stdio.h>
#include <string.h>


int calc_freq(int octave, int inx, float* output) {
	const float melody[] = { 261.764, 277.313, 293.786, 311.237, 329.724, 349.310, 370.059, 392.041, 415.329, 440, 466.136, 466.136, 493.923 };
	
	if (inx < 0 || inx > 12) return -1;

	float result = melody[inx];
	while (octave != 4) {
		if (octave < 4) {
			result /= 2;
			octave++;
		} else {
			result *= 2;
			octave--;
		}
	}

	*output = result;
	return 0;
}
int get_octave() {
	int octave = -500;
	printf("��Ÿ��: ");
	scanf("%d", &octave);

	while (octave == -500 && getchar() != '\n');

	if (octave < -100 || octave > 100) return -500;
	return octave;
}
int get_melody_no() {
	const char melody[13][4] = { "��", "��#", "��", "��#", "��", "��", "��#", "��", "��", "��#", "��" };

	char input[10];
	char c;

	printf("����: ");
	if ((c = getchar()) != '\n') {
		input[0] = c;
	}

	scanf("%8s", input + (c != '\n' ? 1 : 0));
	for (int i = 0; i < 13; i++) {
		if (strcmp(input, melody[i]) == 0) return i;
	}

	return -1;
}

int main() {
	while (1) {
		int octave = get_octave();
		if (octave == -500) { printf("(����) ��Ÿ�� �Է��� ���ڰ� �ƴϰų� ��� ������ �ʰ���\n"); continue; }
		
		int melody_no = get_melody_no();
		if (melody_no == -1) { printf("(����) �������� �ʴ� ����\n"); continue; }
		
		float result = 0;
		if (calc_freq(octave, melody_no, &result) == -1) continue;
		
		printf("���ļ�: %f\n", result);
	}
}