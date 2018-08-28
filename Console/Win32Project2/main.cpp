#include <stdio.h>

void ConOut();
void ConIn();
void Handler();
void GotoXy();
void ConMode();
void MouseInput();
void CharAttr();
void ChgCursor(int argc, char* argv);
void AnotherBuffer();

/* 직접 예제 소스를 확인해 보는 것을 추천합니다. */

int main()
{
	int sw;

	puts("1 : ConOut");
	puts("2 : ConIn");
	puts("3 : Handler");
	puts("4 : GotoXy");
	puts("5 : ConMode");
	puts("6 : MouseInput");
	puts("7 : CharAttr");
	puts("8 : ChgCursor");
	puts("9 : AnotherBuffer");
	puts("etc : exit");
	printf("select in : ");

	scanf_s("%d", &sw);

	while(1) {
		switch (sw) {
		case 1:
			ConOut();
			break;
		case 2:
			ConIn();
			break;
		case 3:
			Handler();
			break;
		case 4:
			GotoXy();
			break;
		case 5:
			ConMode();
			break;
		case 6:
			MouseInput();
			break;
		case 7:
			CharAttr();
			break;
		case 8:
			ChgCursor(1, "");
			break;
		case 9:
			AnotherBuffer();
			break;
		default:
			return 0;
		}
	}
	return 0;
}