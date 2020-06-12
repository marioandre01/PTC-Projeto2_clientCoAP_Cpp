/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   coapPdu.cpp
 * Author: marioandre
 * 
 * Created on 15 de Dezembro de 2018, 20:58
 */

#include "coapPdu.h"

coapPdu::coapPdu(){
}

coapPdu::coapPdu(int n){
    //calloc - Aloca um bloco de memória para uma matriz de elementos numéricos , 
    //cada um deles dimensiona bytes e inicializa todos os bits para zero. 
    pduCoap = (char*) calloc (n,sizeof(char)); //cria um array de tamanho n
    
    tamanhoPduCoap = n;
    
}

coapPdu::coapPdu(const coapPdu& orig) {
}

coapPdu::~coapPdu() {
}

int coapPdu::getSizePduCoap(){
    return tamanhoPduCoap;
}

void coapPdu::setVersion(versao_t versao){
    
    pduCoap[0] &= 0x3F;  // 0x3F = 0011 1111 zerando os bit 6 e 7
    pduCoap[0] |= versao;
}

void coapPdu::setType(type_t type){
    pduCoap[0] &= 0xCF;  // 0xCF = 1100 1111 zerando os bit 4 e 5
    pduCoap[0] |= type;
}

void coapPdu::setTLK(tlk_t tlk){
    pduCoap[0] &= 0xF0;  // 0xF0 = 1111 0000 zerando os bit 0, 1, 2, e 3
    pduCoap[0] |= tlk;
}

void coapPdu::setCode(code_t code){
    pduCoap[1] &= 0x00;  // 0x0 = 0000 0000 zerando os bits de 0 a 7
    pduCoap[1] |= code;
}

void coapPdu::setMsgID(){
 
    pduCoap[2] &= 0x00; // 0x0 = 0000 0000 zerando os bits de 0 a 7
    pduCoap[3] &= 0x00; // 0x0 = 0000 0000 zerando os bits de 0 a 7
    
    uint16_t messageID;
   
   //numero aleatorio 
   mt19937 gen(rd());
   uniform_int_distribution<> dis(0, 10000); //numero aleatorio de 0 a 10000
   
   messageID = dis(gen); // To generate a number: dis(gen)
    
   //cout << "messageID: " <<  messageID << endl;
    
   //Message ID
   pduCoap[2] = (uint8_t) (messageID >> 8); //desloca os bits de 8 a 15, 8 casas a direita
   pduCoap[3] = (uint8_t) messageID; //pega os bits de 0 a 7
   
}

char* coapPdu::getPointerCoapPdu() {
	return pduCoap;
}

void coapPdu::setURI(char * uri, int tamanhoUri){
    
    uint8_t opcaoDelta = URI_PATH - opcaoDeltaAnterior;
    
    uint8_t optionLength = tamanhoUri;
    
    pduCoap[4] |=  (opcaoDelta << 4) | optionLength;
    
    for(int i=0; i < tamanhoUri; i++){
         pduCoap[i+5] = uri[i];
    } 
   
    
}
