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
