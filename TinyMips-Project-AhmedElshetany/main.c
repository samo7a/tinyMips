//
//  main.c
//  TinyMips-Project-AhmedElshetany
//
//  Created by Ahmed  Elshetany  on 7/9/20.
//  Copyright © 2020 Ahmed  Elshetany . All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


void dream (double t) {
    for (int c = 1; c <= t*10000; c++) for (int d = 1; d <= t *10000; d++){}
}

typedef struct {
    int opcode, rx, ry, rz;
} Instruction;
int main() {
    int pc = 0;  // program counter
    int im [500];  // instruction memory
    int dm [16];   // data memory
    int rf [8];    // register file
    int idcu, idx, idy, idz; // instruction decode variables
    int excu, exx, exy, exz; // execute variables
    int dmcu, dmx, dmy, dmz; // Data MEM  variables
    int wbcu, wbx, wby, wbz; // Write Back  variables
    Instruction ir;   // instruction register
    int mar, mar2;   // memory address memory
    int mdr, mdr2;   // memory data register
    int ifid[4], idex[4], exdm[4], dmwb[4];  // buffers
    
    FILE * input = fopen("input.txt", "r"); // open file to get the instructions
    printf("Loading Instructions into IM");
    for(int j = 0; j < 2; j++){
        dream (1.5);
        printf("."); dream (1.5);
    }
    printf(".\n"); dream (1.5);
    
    // reading instructions from the txt file
    int i = 0;
    int count = 0;
    while (!feof(input)){
        int number;
        fscanf(input, "%d ", &number);
        im[i] = number;
        i++;
        count++;
    }
    fclose(input); // close the file
    
    
    // Printing the file contents
    printf("Printing Instructions");
    for(int j = 0; j < 2; j++){
        dream (2);
        printf("."); dream (2);
    }
    printf(".\n"); dream (2);
    dream (2);
    for (int i = 0; i < count; i = i + 4){
        printf("%d %d %d %d\n", im[i], im[i+1], im[i+2], im[i+3]);
        dream (2);
    }
    
    
    // translating the machine code to assembly and print it
    printf("Assembling Program");
    for(int j = 0; j < 2; j++){
        dream (2);
        printf("."); dream (2);
    }
    printf(".\n"); dream (2);
    printf("Program Assembled.\n"); dream (2);
    
    printf("Printing Assembly Instructions");
    for(int j = 0; j < 2; j++){
        dream (2);
        printf("."); dream (2);
    }
    printf(".\n"); dream (2);
    for (int i = 0; i < count; i = i + 4){
       // printing the assembly langauge associated to the machine code
        switch (im[i]) {
            case 1:
                printf("lw   %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 2:
                printf("add  %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 3:
                printf("sw   %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 4:
                printf("sub  %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 5:
                printf("sio1 %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 6:
                printf("sio2 %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 7:
                printf("halt\n"); dream (2);
                break;
            case 8:
                printf("jmp  %d %d %d\n", im[i+1], im[i+2], im[i+3]);  dream (2);
                break;
            case 9:
                printf("beqz %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            case 10:
                printf("ori  %d %d %d\n", im[i+1], im[i+2], im[i+3]); dream (2);
                break;
            default:
                break;
        }
    }
    
    printf("Executing The Program...\n"); dream (2);
    
    // Fetching the first instruction
    int halt = 1;
    mar = pc;
    ir.opcode = im[mar];
    ir.rx = im[mar + 1];
    ir.ry = im[mar + 2];
    ir.rz = im[mar + 3];
    
    //Buffer 1
    ifid[0] = ir.opcode;
    ifid[1] = ir.rx;
    ifid[2] = ir.ry;
    ifid[3] = ir.rz;
    printf("**** Fetching the First Instruction ****\n"); dream(1);
    printf("Program counter = %d\n", pc); dream(2);
    printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
    dream(2);
    printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
    dream(2);
    printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
    dream(2);
    printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
    dream(2);
    printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
    dream(2);
    
    
    while (halt) { // we will be kicked out the while loop when halt = 0;
        switch (ir.opcode) {
            case 1: // lw: load word from memory to a register
  // for all the instructions we get the instruction from ifid buffer and fetch the next instruction at the same time
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4; // increment the program counter
                idx =   ifid[1];      mar = pc;    // mar gets pc
                idy =   ifid[2];      mdr = im[mar];  // mdr get the opcode from the instruction memory
                idz =   ifid[3];      ir.opcode = mdr;  // update the instruction register
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode; // updating the IFID buffer
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = idy;
                idex[3] = idz;
                
                printf("***** Load what in Memory Address %d into Register # %d *****\n", idz , idx);
                dream(2);
                
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = exy;
                exdm[3] = exz;
                
                
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
                
                mar2 = dmz;
                mdr2 = dm[mar2];
                dmz = mdr2;
                
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
                
                //write back
                
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                rf[wbx] = wbz;
                
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 2: // add: add 2 varibles
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                int v1 = rf[idy];
                int v2 = rf[idz];
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = v1;
                idex[3] = v2;
            
            printf("***** Add contents of Regiseters # %d and # %d and write back to Register # %d *****\n", idy , idz, idx);
            dream(2);
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                
                int v3 = exy + exz;
                if (rf[3] == 0) v3 = 0;
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = 0;
                exdm[3] = v3;
            
            
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
            
            
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
            
                //write back
            
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
            
                rf[wbx] = wbz;
                
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 3: // sw: store word from register to memory
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                
                v1 = rf[idx];
                idex[0] = idcu;
                idex[1] = v1;
                idex[2] = 0;
                idex[3] = idz;
            
                printf("***** Store what in Register # %d into Memory Address %d *****\n", idx , idz);
                dream(2);
                
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                

                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = exy;
                exdm[3] = exz;
            
            
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
                
                mdr2 = dmx;
                mar2 = dmz;
                dm[mar2] = mdr2;
            
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
            
                //write back
            
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 4: // sub: subtract 2 varibles
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                v1 = rf[idy];
                v2 = rf[idz];
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = v1;
                idex[3] = v2;
            
            printf("***** Subtract contents of Regiseters # %d from # %d and write back to Register # %d *****\n", idz , idy, idx);
            dream(2);
                
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                
                v3 = exy - exz;
                if (v3 < 0) v3 = 0;
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = 0;
                exdm[3] = v3;
            
            
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
            
            
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
            
                //write back
            
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
            
                rf[wbx] = wbz;
                
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 5: // sio1: take input from the user from the keyboard.
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
               
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = idy;
                idex[3] = idz;
            
            
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                printf("Taking Input from The User (From Keyboard, Numbers Only). Enter a Value ... \n");
                scanf("%d", &v3);
                dream(2);
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = 0;
                exdm[3] = v3;
            
            
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
            
            
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
            
                //write back
            
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
            
                rf[wbx] = wbz;
                
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 6: // si02: print something on the screen
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                v3 = rf[idx];
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = idy;
                idex[3] = v3;
            
            
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                
                printf("Output to Screen ... %d\n", exz); dream(1.3);
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = 0;
                exdm[3] = v3;
            
            
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
            
            
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
            
                //write back
            
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 7: // sio3: halt/stop the program
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = idy;
                idex[3] = idz;
                
                
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                
                halt = 0;
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = exy;
                exdm[3] = exz;
                
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
                

                
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
                
                //write back
                
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                
                printf("***** Halting / Ending the program *****\n");
                dream(2);
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                
                
                break;
                
             case 8: // jmp: jump to specific instruction
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                
                idex[0] = idcu;
                idex[1] = idx;
                idex[2] = idy;
                idex[3] = idz;
                
                
                printf("***** Jumping to Memory Address # %d *****\n",idz);
                dream(2);
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
               
                pc = exz;
                mar = pc;
                ir.opcode = im[mar];
                ir.rx = im[mar + 1];
                ir.ry = im[mar + 2];
                ir.rz = im[mar + 3];
    
                ifid[0] = ir.opcode;
                ifid[1] = ir.rx;
                ifid[2] = ir.ry;
                ifid[3] = ir.rz;
    
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = exy;
                exdm[3] = exz;
                
                
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
                
                mar2 = dmz;
                mdr2 = dm[mar2];
                dmz = mdr2;
                
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
                
                //write back
                
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                
                rf[wbx] = wbz;
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
                
            case 9: // beqz: if rx = 0; jump to the next instruction.
                // operand decode      // fetch
                idcu =  ifid[0];      pc = pc + 4;
                idx =   ifid[1];      mar = pc;
                idy =   ifid[2];      mdr = im[mar];
                idz =   ifid[3];      ir.opcode = mdr;
                                      ir.rx = im[mar + 1];
                                      ir.ry = im[mar + 2];
                                      ir.rz = im[mar + 3];
                                      ifid[0] = ir.opcode;
                                      ifid[1] = ir.rx;
                                      ifid[2] = ir.ry;
                                      ifid[3] = ir.rz;
                
                v1 = rf[idx];
                idex[0] = idcu;
                idex[1] = v1;
                idex[2] = idy;
                idex[3] = idz;
                
                printf("***** Checking If Register # %d equals zero *****\n",  idx);
                dream(2);
                
                // execute
                excu = idex[0];
                exx = idex[1];
                exy = idex[2];
                exz = idex[3];
                if (exx == 0) {
                    pc = pc + 4;
                    mar = pc;
                    mdr = im[mar];
                    ir.opcode = mdr;
                    ir.rx = im[mar + 1];
                    ir.ry = im[mar + 2];
                    ir.rz = im[mar + 3];
                    ifid[0] = ir.opcode;
                    ifid[1] = ir.rx;
                    ifid[2] = ir.ry;
                    ifid[3] = ir.rz;
                }
                
                exdm[0] = excu;
                exdm[1] = exx;
                exdm[2] = exy;
                exdm[3] = exz;
                
                // DM
                dmcu = exdm[0];
                dmx = exdm[1];
                dmy = exdm[2];
                dmz = exdm[3];
                

                
                dmwb[0] = dmcu;
                dmwb[1] = dmx;
                dmwb[2] = dmy;
                dmwb[3] = dmz;
                
                //write back
                
                wbcu = dmwb[0];
                wbx  = dmwb[1];
                wby  = dmwb[2];
                wbz = dmwb[3];
                
                printf("Program counter = %d\n", pc); dream(2);
                printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                dream(2);
                printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                dream(2);
                printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                dream(2);
                printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                dream(2);
                printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                dream(2);
                break;
        
                case 10: // ori: set a register to an immediate value
                // an instruction that I have to create to load 1 into register # 1 for the successive sum.
                    // operand decode      // fetch
                    idcu =  ifid[0];      pc = pc + 4;
                    idx =   ifid[1];      mar = pc;
                    idy =   ifid[2];      mdr = im[mar];
                    idz =   ifid[3];      ir.opcode = mdr;
                                          ir.rx = im[mdr + 1];
                                          ir.ry = im[mdr + 2];
                                          ir.rz = im[mdr + 3];
                                          ifid[0] = ir.opcode;
                                          ifid[1] = ir.rx;
                                          ifid[2] = ir.ry;
                                          ifid[3] = ir.rz;
                    
                    
                    idex[0] = idcu;
                    idex[1] = idx;
                    idex[2] = idy;
                    idex[3] = idz;
                    
                printf("***** Set The value %d into Register # %d *****\n", idz, idx);
                dream(2);
                    
                    
                    // execute
                    excu = idex[0];
                    exx = idex[1];
                    exy = idex[2];
                    exz = idex[3];
                    
                    
                    
                    exdm[0] = excu;
                    exdm[1] = exx;
                    exdm[2] = exy;
                    exdm[3] = exz;
                    
                    // DM
                    dmcu = exdm[0];
                    dmx = exdm[1];
                    dmy = exdm[2];
                    dmz = exdm[3];
                    

                    
                    dmwb[0] = dmcu;
                    dmwb[1] = dmx;
                    dmwb[2] = dmy;
                    dmwb[3] = dmz;
                    
                    //write back
                    
                    wbcu = dmwb[0];
                    wbx  = dmwb[1];
                    wby  = dmwb[2];
                    wbz = dmwb[3];
                    
                    rf[wbx] = wbz;
                
                    printf("Program counter = %d\n", pc); dream(2);
                    printf("Register File Status: RF[] = {%d, %d, %d, %d, %d, %d, %d, %d}\n", rf[0] ,rf[1] , rf[2] , rf[3] , rf[4] , rf[5] , rf[6] , rf[7]);
                    dream(2);
                    printf("IFID Buffer Status: IFID[] = {%d, %d, %d, %d}\n", ifid[0] ,ifid[1] , ifid[2] , ifid[3]);
                    dream(2);
                    printf("IDEX Buffer Status: IDEX[] = {%d, %d, %d, %d}\n", idex[0] ,idex[1] , idex[2] , idex[3]);
                    dream(2);
                    printf("EXDM Buffer Status: EXDM[] = {%d, %d, %d, %d}\n", exdm[0] ,exdm[1] , exdm[2] , exdm[3]);
                    dream(2);
                    printf("DMWB Buffer Status: DMWB[] = {%d, %d, %d, %d}\n\n\n", dmwb[0] ,dmwb[1] , dmwb[2] , dmwb[3]);
                    dream(2);
                    break;
                
                
            default:
                break;
        }
        
    }
    return 0;
}



