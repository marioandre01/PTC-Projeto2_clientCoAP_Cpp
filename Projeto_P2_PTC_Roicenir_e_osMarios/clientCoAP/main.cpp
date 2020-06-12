/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marioandre, marioallan e roicenir
 *
 * Created on 15 de Dezembro de 2018, 20:57
 */

#include <cstdlib> //rand esta nessa biblioteca
#include <iostream>
#include <stdio.h>
#include "UDPSocket.h"
#include "coapPdu.h"

using namespace std;

/*
 * 
 */

void dump(char * buffer, int len) {
    int m = 0, line = 0;

    while (m < len) {
        //printf("%02X: ", line * 16);

        for (int n = 0; n < 32 and m < len; n++, m++) {
            int x = (unsigned char) buffer[m]; //(unsigned char), não permite armazenar valores negativos, e portanto pode representar números em um intervalo que vai de 0 até 255.
            printf("%02X ", x);
        }
        puts("");
        line++;
    }
}

void convert_str_array(string s, char *a) {
    int total = 0;
    //pegando caracteres da string e colocando no array
    while (s[total] != '\0') {
        a[total] = s[total];
        total++;
    }
}

int num_caracter(char *str) {
    int cont = 0;
    for (; *str; str++) cont++;
    return cont;
}

char * stringCharPoint(string s){

    char *c = new char[s.length()+1];
    memcpy(c, s.c_str(), s.length() + 1);
  
    return c;
}

int main(int argc, char** argv) {
    
    if(argc < 2){
        cout << "É necessário informar o IP e a porta e recurso (se necessario)" << endl;
        cout << "Ex: ./coapPdu 127.0.0.1 5683" << endl;
        cout << "Ex: ./coapPdu 127.0.0.1 5683 time" << endl;
        
        return 0;
    }
    
    
    //Dados para criar a conexao
    string ip = argv[1]; // 127.0.0.1
    int porta = atoi(argv[2]); //converter o argumento 5683 de char * para int
    string recurso;
    
    if(argc == 4){
        recurso = argv[3];  //recurso
    }
    
    //cout << "Recurso: " << recurso.size() << endl;
    
    //Criando o Socket UDP
    UDPSocket client;

    int tamanhoPdu;
    
     if(argc == 3){
         tamanhoPdu = 4;
     }
     
     if(argc == 4){
         tamanhoPdu = 4 + recurso.size() + 1;
     }
    
    //cout << "tamanho array pdu: " << tamanhoPdu << endl;
    
    //Criando uma PDU CoAP 
    coapPdu pdu(tamanhoPdu);
   
    

    //Preenchendo os campos da PDU CoAP essenciais
    pdu.setVersion(coapPdu::VERSAO_01);
    pdu.setType(coapPdu::TYPE_CONFIRMABLE);
    pdu.setTLK(coapPdu::TLK_ZERO);
    pdu.setCode(coapPdu::CODE_GET);
    pdu.setMsgID(); //gerar mensagem ID
    
    if(argc == 4){
        pdu.setURI(stringCharPoint(recurso), recurso.size()); //stringCharPoint(recurso) converte string para char *
    }
    
    //Buffer para receber a resposta do servidor CoAP
    char bufferResposta[512] = {};

    try {
        // conecta no servidor do CoAP    
        client.send(pdu.getPointerCoapPdu(), pdu.getSizePduCoap(), ip, porta); //5683 - porta padrão do servidor CoAP
       
        string addr;
        int port;

        cout << "Aguardando receber resposta" << endl;

        string dados = client.recv(512, addr, port); //enquanto nao receber uma resposta fica travado aqui o código

        cout << "Recebeu " << dados.size() << " caracteres de " << addr << ":" << port << " --> " << dados << endl;

        //converter a string em char[]
        convert_str_array(dados, bufferResposta);
        
        //pega o numero de caracteres do char[]
        int tbr = num_caracter(bufferResposta);

        //mostrar o conteudo do char[] em HEX
        dump(bufferResposta, tbr);


    } catch (UDPSocket::SocketException e) {
        perror("ao enviar");
    }


    return 0;

}
