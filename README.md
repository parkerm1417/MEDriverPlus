# ME Driver Plus 

This code was written for use with the Robinson Lab ME Driver Circuit and the NUCLEO-H755ZI-Q. It is used to do bidirectional communication and powering of ME films.

## Adjusting Code for Individual Use

### Changing Driving Frequency

  1. Open MEDriverPlus_CM7/Core/Inc/TimingCtrl.h
  2. Change the value on Line 7 that is bolded below
     > ```#define DRIVER_FREQ 218000``` will have a driver frequency of 218kHz\

### Changing Downlink Timing

  1. Open MEDriverPlus_CM7/Core/Inc/TimingCtrl.h
  2. Change values on lines 10 and 11 for timing when sending a 0
     > Values are in microseconds
  3. Change values on lines 13 and 14 for timing when sending a 1
     > Values are in microseconds

### Creating a New Message

  1. Open MEDriverPlus_CM7/Core/Inc/MsgCtrl.h
  2. Add the name of your message to the enumeration on line 8, but ensure that the last listing in the enumeration is *NumberOfMessages*
     > ```
     > enum MessageList{
	   >   Message1,
     >   Message2,
     >   NumberOfMessages
     > };
     > ```
  3. Open MEDriverPlus_CM7/Core/Src/MsgCtrl.c
  4. Create a new struct near the top of the code mimicing the struct found at line 5
     > ```
     > struct Message Message1_ = {
     >   .DownLength = 5,
     >   .Data = 0b01010,
     >   .UpLength = 2
     > };
     > ```
     > - The name of the struct can be whatever you want, but to make it east consider picking the name used in Step 2 in the enum list and adding an underscore after
     > - .DownLength is the number of bits this message is to downlink
     > - .Data is the data that will be downlinked during the message
     > - .UpLength (optional) is the number of bits to be read over uplink after data is downlinked
  5. At the beginning of the ```Setup_MsgCtrl``` method on line 11, add a line of code that sets the index of the Messages array to the struct created in step 4
     > ```Messages[Message1] = Message1_;```

### Sending a Message
  1. Open MEDriverPlus_CM7/Core/Src/MEDriverPlusMain.c
  2. Within the ```Loop``` method, ```BspButtonState == BUTTON_PRESSED``` returns true when the blue user button is pressed on the NUCLEO board
  3. Inside of ```if (BspButtonState == BUTTON_PRESSED)``` use the SendMessage method to send a message
     > ```
     > if (BspButtonState == BUTTON_PRESSED){
     >   SendMessage(Message1);
     > }
     > ```
