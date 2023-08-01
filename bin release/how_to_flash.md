### วิธีการอัปเดตอะแดปเตอร์ CN105Kit V2 (Wifiserial)

1. เตรียม USB to UART และ สายจัมเปอร์สำหรับการ Flash Firmware
2. เชื่อมต่อ USB to UART เข้ากับ CN105Kit V2
   - 5V -> 5V
   - GND -> GND
   - TX -> RX
   - RX -> TX 
4. ปรับตำแหน่งสวิตช์ไปที่ตำแหน่ง **flash mode** 
5. เชื่อมต่อไปที่คอมพิวเตอร์
6. ใช้โปรแกรม [NodeMCU PyFlasher ](https://github.com/marcelstoer/nodemcu-pyflasher/releases/tag/v5.0.0)(หรือโปรแกรมอื่นๆ สำหรับ flash ESP8266 ) โดยใช้การตั้งค่าดังนี้:
   - Upload Speed = 460800
   - Flash Mode = DOUT
   - Erase Flash = NO (หากต้องการคืนค่าโรงงานให้เลือก wipe all)
 7. ทำการ Flash Firmware และรอให้เสร็จ
 8. ปรับตำแหน่งสวิตช์ไปที่ตำแหน่ง **normal mode**
 9. ถอดสายออกแล้วเชื่อมต่อไปที่เครื่องปรับอากาศ

*ตัวโมดูล CN105Kit V2.1 (ใช้ชิพ ESP-12E) สามารถอัปเกรดผ่าน OTA ได้

### Update Guide for CN105Kit V2 (Wifiserial) Hardware

1. Prepare USB to UART adapter + Jumper wires.
2. Connect CN105Kit V2 pins to USB UART.
   - 5V -> 5V
   - GND -> GND
   - TX -> RX
   - RX -> TX 
3. Change the position of the switch to **flash mode** 
4. Connect to the computer.
5. Use [NodeMCU PyFlasher ](https://github.com/marcelstoer/nodemcu-pyflasher/releases/tag/v5.0.0)(or other software) to flash ESP8266 using the following settings:
   - Upload Speed = 460800
   - Flash Mode = DOUT
   - Erase Flash = NO (If you want to save existing settings)
7. Flash the firmware and wait for the process to be completed.
8. Change the position of the switch to **normal mode**
9. Unplug from the computer and re-connect to A/C.
    
*OTA Update is only possible for CN105Kit V2.1 Hardware (using ESP-12E Chip)
