# mrJackServer
2020 오픈소스기반기초설계 팀프로젝트

## 서버-클라이언트 통신

### 1:1 메시지 전송 (2020/11/20)
user1, user2는 server에 순차적으로 메시지를 전송한다.<br>
(순서를 맞춰야함 user1->user2->user1->...)<br>
서버는 받은 메시지를 user1과 user2에게 전송한다.<br>
user1, user2는 메시지를 스레드를 통해 받는다.<br>
##### 현재 user1-user2 통신만 가능
![gameSocket](https://user-images.githubusercontent.com/53012696/99871069-06843980-2c1b-11eb-85ae-e165a8d1b189.gif)

### multi room 1:1 메시지 전송 (2020/11/21)
각 room의 user는 server에 순차적으로 메시지를 전송한다.<br>
(순서를 맞춰야함 user1->user2->user1->...)<br>
서버는 받은 메시지를 user에게 전송한다.<br>
user는 메시지를 스레드를 통해 받는다.<br>
##### 각 room 안의 유저들끼리 통신 가능
![socketThread](https://user-images.githubusercontent.com/53012696/99874663-1e64b900-2c2d-11eb-970f-de4483551ad9.gif)

### 서버에서 유저로 역할 전달 (2020/11/27)
##### 각 유저는 전달받은 역할을 메시지 박스로 띄움
![sendRole](https://user-images.githubusercontent.com/53012696/100411799-1639cd00-30b6-11eb-8fe0-845a29a9f562.gif)

### 서버 접속 실패 시 메시지 박스 띄우기 (2020/12/05)
![connectErr](https://user-images.githubusercontent.com/53012696/101560603-ffc13900-3a06-11eb-98d9-d1bb6408030c.gif)

### gamedata를 파일로 만들어 서버-유저 주고 받기 (~2020/12/09)
잭 역할의 유저가 잭 캐릭터를 확인할 수 있는 메시지 박스를 띄운다. <br>
상대 유저가 사용한 캐릭터의 위치 변경을 확인할 수 있다.<br>
recv를 위해 사용한 스레드를 없애고 gamedata의 라운드에 따라 send와 recv를 하도록 변경했다.<br>
자신의 차례가 아니라면 상대의 차례를 알리는 메시지 박스가 뜨고, 서버로 gamedata가 오는 것을 기다린다.<br>
서버는 유저에게 받은 gamedata의 라운드를 확인하여 홀수/짝수 라운드에 따라 캐릭터 카드 상태를 변경한다.<br>
##### 게임 흐름에 따라 gamedata에 정보를 저장해야하는데 미흡하고 서버가 도중에 중단되는 문제가 발생함
##### 상대가 게임에서 나갔을 경우에 대한 처리가 없음
![changePos](https://user-images.githubusercontent.com/53012696/101559861-62193a00-3a05-11eb-9b56-01e63dbfa525.gif)

<pre> fstream을 이용하여 유저에게 받은 데이터를 파일로 저장한다.
파일의 내용을 버퍼에 담아 유저에게 다시 전달하는 방식을 택했다.
게임이 시작되고 가장 처음에 두 유저에게 역할을 전달하고, 잭을 랜덤으로 골라 게임 데이터에 세팅한다.
그 다음 초기 데이터를 두 유저에게 보낸다.
반면 mfc에서는 스레드로 recv 하던 것을 자신의 턴이 아닐 때 recv 하는 방식으로 바꿨다.
분리된 스레드에서 메인에서 작동하는 함수들을 사용하는데 어려움이 있었다. (공부필요)
mfc의 게임 진행에 따른 자체 데이터와 서버를 통해 주고받는 데이터(GameData)의 연결에 노력했다.
서버에서 데이터를 받으면 그 내용을 mfc 내 사용 데이터로 변경하고,
반대로 서버로 데이터를 보낼 때엔 그 전에 mfc 내 데이터 일부를 GameData에 넣는다.
</pre>
