#include <EEPROM.hdfdf>
#include <IRremote.h>

#define LED1 5
#define LED2 9
#define LED3 10
#define LED4 6

//struct CodBtns {
  // Описание кнопки
//  long code;  // 4 байта на "Код" кнопки
//  int name;  //  Integer на название кнопки
//}

long RECV_PIN = 3; // Определяем пин для приемника

const long kanal = 4; // количество используемых каналов PWM

byte IR_code;
byte IR_code_Clon;

//struct Dynamically {
  // Описание 
//  byte code;  // текущая переменная
//  String name;  //  название
  
//};

long K[kanal+(4+2)];//массив каналов


IRrecv irrecv(RECV_PIN); // Объект приемника
decode_results results; // Регистрируем декодер


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  
  
  irrecv.enableIRIn(); // Включаем приемник  
  Serial.begin (115200); // Задаем скорость обмена com-порта 115200 
  Serial.println();
  Serial.println(F("| setup |"));
  if (EEPROM[0] != 100){ Serial.println(F("| Default_Setting |")); Default_Setting(EEPROM[0]);} // количество кнопок (100 шт. резерв)
 
  //auto on/////
  //K[0]=3;/////
  //K[2]=8;///////
  Demo(2);///  
  //////////////
}
/////////////////////////////////////...................................................................
void loop() {  													 									 //.	
  if (irrecv.decode(&results)){  																	 //.
     irrecv.resume();  																								 //.
    if (results.value != 4294967295){																 //.
      IR_code = results.value, HEX;		 															 //. 	
      Serial.print(F("| IR_in = "));															     //. 
      Serial.print(results.value, HEX); 															 //.
      Serial.print(F(" => "));																		 //.
      Serial.print(IR_code);																		 //.
   //   Serial.print(F(" | | hold=")); Serial.print(results.value);// false-hold test 				 //.
      Serial.println(F(" |"));
      delay(100);																				 //.
      Sverka(IR_code);		
      																				 				 //.
    }																								 //.
 /*   else{																							 //.   
 	Serial.print(F("| IR_in = hold   => "));														 //.   
  	Serial.print(IR_code_Clon);																		 //.
   // Serial.print(F(" | | hold=")); Serial.print(results.value);// false-hold test  				 //.
    Serial.println(F(" | ")); 																		 //.
    delay(400);																						 //.
  																									 //.
    }*/																								 //.
  }																									 //.
}																									 //.
//......................................................................................................



///////////////////////////////////// 						здесь математические действия
void Sverka(byte _Sverka) {
  //1 => EPROM[1]= POWER => ЦИФРА КОДА power
  // 100 кнопок физических на пульт, 6 каналов PWM в Ардуино, + 1 модификатора, (+ 1 адресов кнопки.) = 800 бит :))
  // x1*100=место хранения значения
 
byte x1 = 1;

  for(long i = 1; i < EEPROM[0]+1; i++){                   // ищем код кнопки в горизонтальной плоскости
    //Serial.print("| i=");Serial.print(i);Serial.print(" |"); if (i == 20 || i == 40 || i == 60 ||  i == 80 || i == 100) {Serial.println();}    
    
    if (_Sverka == EEPROM[i]){     
      if (K[1] != EEPROM[i]){ 
       K[1]=EEPROM[i];
       K[2]=EEPROM[i+EEPROM[0]]; 
       K[0]= 0;
      
      if (i >10){for(long j = i; j < EEPROM[0]*5+i; j=j+EEPROM[0]){K[x1]=EEPROM[j];x1++;}}
      }else{K[0]++;}

     Demo(K[2]);  break; 
      }

   
  }
  

} 






void Rutina(){/
/ Перекладываем из пустого в порожне

  
  
  Serial.println();Serial.println("| Rutina |");
  Serial.print("| K[0]=");Serial.print(K[0]);Serial.println(" |"); // количество повторов
  Serial.print("| K[1]=");Serial.print(K[1]);Serial.println(" |"); // номер кнопки
  Serial.print("| K[2]=");Serial.print(K[2]);Serial.println(" |"); // модификатор
  
  Serial.print("| K[3]=");Serial.print(K[3]);Serial.println(" |"); // R
  Serial.print("| K[4]=");Serial.print(K[4]);Serial.println(" |"); // G
  Serial.print("| K[5]=");Serial.print(K[5]);Serial.println(" |"); // B
  Serial.print("| K[6]=");Serial.print(K[6]);Serial.println(" |"); // W
  
    analogWrite(LED1, K[3]); 
	analogWrite(LED2, K[4]); 
	analogWrite(LED3, K[5]); 
	analogWrite(LED4, K[6]);
 
}

/////////////////////////////////////  						здесь cвисто перделки
void Demo(byte _Demo) {

  //Serial.print("_Demo="); Serial.println(_Demo);
  switch (_Demo) {
    //instal mod 
  /*  case 0:{Serial.println(); Serial.println("//instal mod ");
            Serial.print("| K[0]=");Serial.print(K[0]);Serial.println(" |"); // количество повторов
   			Serial.print("| K[1]=");Serial.print(K[1]);Serial.println(" |"); // Номер кнопки
     		Serial.print("| K[2]=");Serial.print(K[2]);Serial.println(" |"); // модификатор
      break;}*/
    //off
    case 1:{K[3]=0; // LED1 R
            K[4]=0; // LED2 G
            K[5]=0; // LED3 B
            K[6]=0; // LED4 W
            K[0]=0; //количество повторов
      		Serial.println("| Led => OFF |");    
      break;}
    //on
    case 2:{ 
            
           /* if (K[3]>50 || K[4]>50 || K[5]>50 || K[6]>50){
              K[3]=0; K[4]=0; K[5]=0; K[6]=0;
            }else{K[3]=255;K[4]=255;K[5]=255;K[6]=255;}          	             
            Serial.println("| All White |");
    		*/
            
      		if (K[0] == 0){ 
              K[3]=255; // LED1 R
          	  K[4]=255; // LED2 G
          	  K[5]=255; // LED3 B
          	  K[6]=255; // LED4 W          	             
              Serial.println("| Led => All White |");}
    		  
     		if (K[0] == 1){ 
              K[3]=255; // LED1 R
          	  K[4]=255; // LED2 G
          	  K[5]=255; // LED3 B
          	  K[6]=0;   // LED4 W 
              Serial.println("| Led => White.RGB |");}
            if (K[0] == 2){ 
              K[3]=0;   // LED1 R
          	  K[4]=0;   // LED2 G
          	  K[5]=0;   // LED3 B
          	  K[6]=255; // LED4 W 
              Serial.println("| Led => Only White|");K[0] = -1;}
              Serial.println("| Led => ON |");
              
    	     
      break;}
    //  -
    case 3:{
      		K[3]=K[3]-20; 
      		K[3] = constrain(K[3], 0, 255);  // LED1 R 
            K[4]=K[4]-20; 
      		K[4] = constrain(K[4], 0, 255);  // LED2 G
            K[5]=K[5]-20; 
      		K[5] = constrain(K[5], 0, 255);  // LED3 B
            K[6]=K[6]-20; 
      		K[6] = constrain(K[6], 0, 255);  // LED4 W
     		//K[0]=0; // количество повторов
      		delay(400);
            
    		
      break;}
    //  +
    case 4:{
      		K[3]=K[3]+20; 
      		K[3] = constrain(K[3], 0, 255);  // LED1 R 
            K[4]=K[4]+20; 
      		K[4] = constrain(K[4], 0, 255);  // LED2 G
            K[5]=K[5]+20; 
      		K[5] = constrain(K[5], 0, 255);  // LED3 B
            K[6]=K[6]+20; 
      		K[6] = constrain(K[6], 0, 255);  // LED4 W
     		//K[0]=0; // количество повторов
      		delay(400);
            
      break;}
    case 5:{K[3]=255;
            K[4]=0;  
            K[5]=0;  
            Serial.println("| Led => RED |");
    		K[0] = -1;      
            	
      break;}
    case 6:{K[3]=0;
           K[4]=255;  
           K[5]=0;       	             
           Serial.println("| Led => Green |");
    	   K[0] = -1;      
            
      break;}
    case 7:{K[3]=0;
            K[4]=0;  
            K[5]=255;           	             
            Serial.println("| Led => Blue |");
    		K[0] = -1;      
           
      break;}
    case 8:{      		
            if (K[6]>50){K[6]=0;}else{K[6]=255;}          	             
            Serial.println("| Led => White |");
    		K[0] = -1;
      	  
      break;}
    
     case 20:{      		         	             
            Serial.println("| Led => EEPROM |");    		
      	    
      break;}
    
   /* 
    default:{
   		    K[3]=0; // LED1 R
            K[4]=0; // LED2 G
            K[5]=0; // LED3 B
            K[6]=0; // LED4 W 
            Rutina();
      Serial.println();Serial.print("Demo="); Serial.println(_Demo);Serial.println("| no action commands found. Contact the author of the sketch at markfamiliytitan@gmail.com |");}
          //выполняется, если не выбран ни одна альтернатива
     */ 
  }

  
  
  Rutina();

} 








/////////////////////////////////////				Установка значения в EEPROM
void Default_Setting(byte _Setting) {
  
  
EEPROM[0]=100; //если должно быть больше кнопок, тогда необходимо переадресовать ячейки
      
  /////..............................................................................................................
           
           		   	   /*  адрес    */ /*модификатор*/
/*    	 off 	   */  EEPROM[1]=255;  EEPROM[101]=1;/*  1-выключить все  \							*/
/* 		 on 	   */  EEPROM[2]=191;  EEPROM[102]=2;/*  2-включить все   \						*/
/* 		down 	   */  EEPROM[3]=239;  EEPROM[103]=3;/*  3-вниз            / обязательные кнопки   	*/
/*		 up   	   */  EEPROM[4]=175;  EEPROM[104]=4;/*  4-верх			  /							*/
/*channel-1 red    */  EEPROM[5]=247;  EEPROM[105]=5;/*  5-канал 1									*/
/*channel-2 green  */  EEPROM[6]=119;  EEPROM[106]=6;/*  6-канал 2									*/
/*channel-3 blue   */  EEPROM[7]=183;  EEPROM[107]=7;/*  7-канал 3									*/
/*channel-4 white-1*/  EEPROM[8]=215;  EEPROM[108]=8;/*  8-канал 4									*/
/*channel-5 white-2*/  EEPROM[9]=0;    EEPROM[109]=9;/*  9-канал 5									*/
/*channel-6 white-3*/  EEPROM[10]=0;   EEPROM[110]=10;/* 10-канал 6									*/
/*.. channel-x.    */
                                                      /* 20-авто вывод из EEPROM						*/   
  
  //test//
  EEPROM[20]=151; EEPROM[120]=20; EEPROM[220]=225; EEPROM[320]=20; EEPROM[420]=255; EEPROM[520]=55;
  EEPROM[21]=167; EEPROM[121]=255; EEPROM[221]=0; EEPROM[321]=255; EEPROM[421]=0;   EEPROM[521]=55;
  EEPROM[22]=87;  EEPROM[122]=20; EEPROM[222]=225; EEPROM[322]=20; EEPROM[422]=255; EEPROM[522]=55;
  EEPROM[23]=103; EEPROM[123]=100; EEPROM[223]=0; EEPROM[323]=100; EEPROM[423]=100; EEPROM[523]=0;
  EEPROM[24]=231; EEPROM[124]=30; EEPROM[224]=20; EEPROM[324]=10; EEPROM[424]=50;   EEPROM[524]=255;
 /* EEPROM[20]=167; EEPROM[120]=20; EEPROM[220]=225; EEPROM[320]=20; EEPROM[420]=255; EEPROM[520]=55;
  EEPROM[20]=167; EEPROM[120]=20; EEPROM[220]=225; EEPROM[320]=20; EEPROM[420]=255; EEPROM[520]=55;
  EEPROM[20]=167; EEPROM[120]=20; EEPROM[220]=225; EEPROM[320]=20; EEPROM[420]=255; EEPROM[520]=55;
  //R
 /* EEPROM[20]=220; EEPROM[120]=20; EEPROM[220]=225; EEPROM[320]=225; EEPROM[420]=0;   EEPROM[520]=0;
  EEPROM[21]=94;  EEPROM[121]=20; EEPROM[221]=225; EEPROM[321]=175; EEPROM[421]=85;  EEPROM[521]=0;
  EEPROM[22]=112; EEPROM[122]=20; EEPROM[222]=225; EEPROM[322]=85;  EEPROM[422]=175; EEPROM[522]=0;
  EEPROM[23]=226; EEPROM[123]=20; EEPROM[223]=225; EEPROM[323]=0;   EEPROM[423]=255; EEPROM[523]=0;
  //G
  EEPROM[24]=243; EEPROM[124]=20; EEPROM[224]=255; EEPROM[324]=0;   EEPROM[424]=255;  EEPROM[524]=0;
  EEPROM[25]=37;  EEPROM[125]=20; EEPROM[225]=175; EEPROM[325]=85;  EEPROM[425]=255;  EEPROM[525]=0;
  EEPROM[26]=124; EEPROM[126]=20; EEPROM[226]=85;  EEPROM[326]=175; EEPROM[426]=255;  EEPROM[526]=0;
  EEPROM[27]=192; EEPROM[127]=20; EEPROM[227]=0;   EEPROM[327]=255; EEPROM[427]=255;  EEPROM[527]=0;
  //B
  EEPROM[28]=128; EEPROM[128]=20; EEPROM[228]=0;   EEPROM[328]=255; EEPROM[428]=255; EEPROM[528]=0;
  EEPROM[29]=240; EEPROM[129]=20; EEPROM[229]=85;  EEPROM[329]=255; EEPROM[429]=175; EEPROM[529]=0;
  EEPROM[30]=45;  EEPROM[130]=20; EEPROM[230]=175; EEPROM[330]=255; EEPROM[430]=85;  EEPROM[530]=0;
  EEPROM[31]=51;  EEPROM[131]=20; EEPROM[231]=225; EEPROM[331]=255; EEPROM[431]=0;   EEPROM[531]=0;
  //W
 /* EEPROM[32]=220; EEPROM[132]=20; EEPROM[232]=225; EEPROM[332]=20; EEPROM[432]=255; EEPROM[532]=0;
  EEPROM[33]=220; EEPROM[133]=20; EEPROM[233]=225; EEPROM[333]=20; EEPROM[433]=255; EEPROM[533]=0;
  EEPROM[34]=220; EEPROM[134]=20; EEPROM[234]=225; EEPROM[334]=20; EEPROM[434]=255; EEPROM[534]=0;
  EEPROM[35]=220; EEPROM[135]=20; EEPROM[235]=225; EEPROM[335]=20; EEPROM[435]=255; EEPROM[535]=0;
*/
  /*EEPROM[30]=220; EEPROM[130]=20; EEPROM[230]=225; EEPROM[330]=20; EEPROM[430]=255; EEPROM[530]=55;
  EEPROM[30]=220; EEPROM[130]=20; EEPROM[230]=225; EEPROM[330]=20; EEPROM[430]=255; EEPROM[530]=55;
  EEPROM[30]=220; EEPROM[130]=20; EEPROM[230]=225; EEPROM[330]=20; EEPROM[430]=255; EEPROM[530]=55;
  EEPROM[30]=220; EEPROM[130]=20; EEPROM[230]=225; EEPROM[330]=20; EEPROM[430]=255; EEPROM[530]=55;*/
} 


