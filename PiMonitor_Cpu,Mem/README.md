# PIMonitor_CPU,Mem
라즈베리파이의 CPU 사용률과 메모리 사용률을 축력한다.

File 구조체 포인트 변수를 만들어서 /proc/stat, /proc/meminfo 파일을 읽어옴

fgets를 통해서 cpu의 경우에는 첫줄을, 메모리의 경우에는 while문을 통해 문자열을,
sscanf로 각 변수에 저장함

cpu, memory 사용률 공식으로 출력하게 된다.

![Alt text](PiMonitor_Cpu,Mem/cpumem.PNG)