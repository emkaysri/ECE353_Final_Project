#!/bin/python

##################################
# ECE 353: 

import serial;
import time;
import random;
from random import shuffle
import sys, getopt

portn = "COM7"
inputfile="image2.txt"


ser = None;
MAX_ROWS = 320


def send_file ( filename ):

  ROWS = 0
  COLS = 0
  print ("Open File:" + filename)
  with open(filename) as fileobj:
    i = 0
    for line in fileobj:
      if i == 0:
        tmp = line.split(':');
        COLS = int(tmp[1].rstrip()) 
      elif i == 1:
        tmp = line.split(':');
        ROWS = int(tmp[1].rstrip()) 
      else:
        string_list = line.split(',');

      i = i + 1;

  rand_index = ROWS * [0]
  for i in range (0, ROWS):
      rand_index[i] = i

  shuffle(rand_index) 

  send_start()
  send_rows(ROWS)
  send_line_size(COLS*3)

  for row_index in range (0, ROWS ):
    send_line_num( ((MAX_ROWS - ROWS) >> 1)+rand_index[row_index]);
    row_list = string_list[ rand_index[row_index]*COLS*3 : (rand_index[row_index]*COLS + COLS)*3]
    send_data(row_list)  
  
  return

def send_start ():
  cmd = str.encode("STRT");
  ser.write(cmd);
  wait_for_ack()
  return

def send_rows ( rows ):
  cmd = str.encode("HGHT");
  ser.write(cmd);
  wait_for_ack()
  row_bytes = str.encode(format(rows,'04d'));
  ser.write(row_bytes);
  wait_for_ack()
  return


def send_line_num ( line_num ):
  line_cmd = str.encode("LINE");
  ser.write(line_cmd);
  wait_for_ack()
  line_bytes = str.encode(format(line_num,'04d'));
  ser.write(line_bytes);
  wait_for_ack()
  return

def send_line_size ( num_bytes ):
  line_cmd = str.encode("WDTH");
  ser.write(line_cmd);
  wait_for_ack()
  data = str.encode(format(num_bytes,'04d'));
  ser.write(data);
  wait_for_ack()
  return

def send_data ( data ):
  line_cmd = str.encode("DATA");
  ser.write(line_cmd);
  wait_for_ack()

  i = len(data)

  while( i > 0) :
    data_byte = data.pop(0);
    uart_packet = int(data_byte, 16).to_bytes(1, byteorder="big");
    ser.write(uart_packet);
    i = i - 1;

  wait_for_ack()
  return

def wait_for_ack ():
  while ( str.encode("OK\n") != ser.readline() ):
    pass
  return

if __name__ == "__main__":
  print ("##########################################")
  print ("# ECE 353 HW2")
  print ("##########################################")
  ser = serial.Serial(portn, 1152000, timeout=2);
  ser.reset_input_buffer();
  ser.reset_output_buffer();
  print ("-- Opened COM port "+ser.name) 

  send_file(inputfile);
  ser.close();
  print ("##########################################")
