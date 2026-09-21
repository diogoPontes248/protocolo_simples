# protocolo_simples
Protocolo simples para vizualizar os principais problemas de protocolos estudado em arquitetura de redes de computadores.

O protocolo original se baseia nas seguintes regras:
- 1: Se a recepção anterior foi livre de erro, a próxima mensagem no sentido contrário levará um ACK; caso contrário a próxima mensagem no sentido contrário levará um NAK.
- 2: Se a recepção anterior foi um NAK, ou foi uma primitiva de ERR, retransmite a primitiva antiga; qualquer outro caso procure por uma nova primitiva para transmissão.  

## Resultado:

Ao colocarmos a porcentagem de erro em 0 e executarmos o programa, veremos que não ocorreu nenhum problema em ambas as mensagens recebidas por A e B.
```
A recebeu: ZYXWVUTSRQPOMNLKJIHGFEDCBA
B recebeu: ABCDEFGHIJKLMNOPQRSTUVWXYZ
```
Entretanto, ao elevarmos um pouco a porcentagem de erro, veremos problemas como a duplicação de caracteres e em algumas ocasiões perda dos dados finais.
```
A recebeu: ZYXXXWVUTSSRQPOOOMNLKJJIIHHHGFEDCBA
B recebeu: ABCDEFGGHIIJKLMMNOPQRSTUUVVVWWXYZ
```
