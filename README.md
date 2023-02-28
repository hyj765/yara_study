
### yara 룰 생성 방법

```
rule sample
{
  string:
      $v = "test" nocase
      $b = { EF BB BF 20 20 61 68 6F 63 6F 72 61 73 69 63 6B }
  condition:
      $v or &b
}

```

다음과 같이 입력하면 sample이란 룰이 생성된다.
이 때 String은 탐색할 때 사용할 문자열 또는 바이너리 즉 hex 값을 말한다.
이와 같은 탐지 방식에는 정규 표현식도 사용이 가능하다.

condition은 해당 탐지 여부를 결정하는 값이라 생각하면된다.
이는 참과 거짓여부로 반환해주며 이 값에는 or and와 같이 사용함으로써 
해당 결과 값을 결정 지을 수 있다.
