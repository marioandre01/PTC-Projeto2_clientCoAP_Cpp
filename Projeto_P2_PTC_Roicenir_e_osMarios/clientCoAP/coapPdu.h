/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   coapPdu.h
 * Author: marioandre
 *
 * Created on 15 de Dezembro de 2018, 20:58
 */

#ifndef COAPPDU_H
#define COAPPDU_H

#include <stdlib.h>  // calloc
#include <cstdlib> //rand esta nessa biblioteca
#include <iostream>
#include <random>

using namespace std;

class coapPdu {
public:

    enum versao_t {
        VERSAO_01 = 0x40 // 0x40 = 0100 0000
    };
    
    enum type_t {
        TYPE_CONFIRMABLE = 0x00,  //0x00 = 0000 0000
        TYPE_NON_CONFIRMABLE = 0x10,  //0x10 = 0001 0000
        TYPE_ACKNOWLEDGEMENT = 0x20,  //0x20 = 0010 0000
        TYPE_RESET = 0x30  //0x30 = 0011 0000
    };
    
    enum tlk_t {
        TLK_ZERO = 0x00 //0x00 = 0000 0000
       
    };
    
    //code = c.dd = 8 bits - 000(c) 00000(dd)
    //c = 3 bits -> request (0 - 000), a success response (2 - 010), a client error response (4 - 100), or a server error response (5 - 101)
    //dd = 5 bits -> (01 = 00001 - GET), (02 = 00010 - POST), (03  =00011 - PUT), (04 = 00100 - DELETE)
    enum code_t {
        CODE_GET = 0x01,   //0x01 = 0000 0001
        CODE_POST = 0x02,  //0x02 = 0000 0010
        CODE_PUT = 0x03,   //0x03 = 0000 0011
        CODE_DELETE = 0x04 //0x04 = 0000 0100
       
    };
    
    enum option_delta_t {
        IF_MATCH = 0x01,   
        URI_HOST = 0x03,  
        ETAG = 0x04,   
        IF_NONE_MATCH = 0x05, 
        URI_PORT = 0x07, 
        LOCATION_PATH = 0x08,
        URI_PATH = 0x0B, 
        CONTENT_FORMAT = 0x0C,
        MAX_AGE = 0x0E, 
        URI_QUERY = 0x0F, 
        ACCEPT = 0x11, 
        LOCATION_QUERY = 0x14,
        PROXY_URI = 0x23,
        PROXY_SCHEME = 0x27,
        SIZEL = 0x3C,
       
    };


    coapPdu();
    coapPdu(int n);
    coapPdu(const coapPdu& orig);

    int getSizePduCoap();   
    void setVersion(versao_t versao);
    void setType(type_t type);
    void setTLK(tlk_t tlk);
    void setCode(code_t code);
    void setMsgID();
    char* getPointerCoapPdu();
    void setURI(char * uri, int tamanhoUri);
    

    
    virtual ~coapPdu();
    
private:
    
    int tamanhoPduCoap;
    char * pduCoap;
    random_device rd; //numero aleatorio
    uint8_t opcaoDeltaAnterior = 0;
   
};

#endif /* COAPPDU_H */

