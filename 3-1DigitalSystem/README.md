# FPGA Tool



## Background

### Field Programmable Gate Array
- 2016년까지 FPGA 시장은 1위 자일링스(53%)와 2위 인텔(구 알테라, 인텔에게 인수 36%)
- 자일링스 회사의 FPGA 는 자율주행차에 많이 사용된다고 함.
- 지금 실습할 때 사용하는 Quartus 는 intel 의 FPGA Tool 임.

<br>

## Env

### Project
- Empty project
- Device : MAX II
- Simulation : ModelSim

<br>

### File
- Block Diagram

<br>

## Issues

- block diagram 의 각 node 들의 이름이 똑같으면 안 됨.
- project 이름을 정할 때 linux 명령어 system 에 영향을 주는 어떤 특수기호라도 있으면 안 됨. 예를 들어, '-' 라거나, '.' 라거나. 그 이유는 linux 명령어를 이용하여 simulation 등을 돌리기 때문.
- windows user name 한글이면 경로가 한글이라 안 됨.
- node (게이트) 이름 첫글자 숫자이면 안 됨.



## preview

- ..


