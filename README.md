# Industrial CAN IoT Gateway  
STM32F4 + STM32G0 + MCP2515 + ESP8266

This repository contains a demo **Industrial CAN + IoT Gateway** system built with:

- **IOT_GATEWAY** – STM32F401-based CAN + Wi-Fi gateway with TFT display  
- **IOT_node** – STM32G0-based CAN sensor node with LM35 temperature sensing  

The goal is to collect temperature data from CAN nodes, display it locally on a TFT screen, and push it to a remote server via Wi-Fi (ESP8266).  
Both projects are developed using **STM32CubeIDE** and the **MCP2515** SPI CAN controller.


## 1. System Overview

### IOT_GATEWAY (STM32F401RBT6)

- Acts as a **CAN master / gateway**
- Interfaces with **MCP2515** over **SPI2** for CAN communication
- Uses **ESP8266** (on **USART6**) to send readings to a backend server via HTTP GET:
  - `GET /page.php?temp=<temp>&hum=64&dev=<node>`
- Renders data and basic UI on a **1.8" ST7735 TFT** (SPI1)
- Two user switches:
  - **SW_UP** → Request data from one CAN node (e.g. Node 1)
  - **SW_DN** → Request data from another CAN node (e.g. Node 2)
- Status LEDs and a buzzer for basic feedback
- Optional **16×2 LCD** support (driver present, usage mostly commented in code)

### IOT_node (STM32G030F6Px)

- Acts as a **CAN temperature node**
- Reads temperature from an **LM35** analog sensor using **ADC1 (Channel 0)**
- Uses **MCP2515** over **SPI1** to connect to the CAN bus
- Node ID is selected using a **3-bit DIP switch**:
- On receiving a CAN frame with ID equal to its `NODE`:
  - Blinks a status LED
  - Samples the LM35
  - Sends a CAN response frame with the temperature value in `data[0]`


## 2. Repository Structure

```
Industrial-CAN-IoT-Gateway/
├─ IOT_GATEWAY/   # STM32F401RBT6 gateway project (STM32CubeIDE)
│  ├─ Core/
│  │  ├─ Src/
│  │  │  ├─ main.c          # Gateway application logic
│  │  │  ├─ CANSPI.c        # CAN over MCP2515
│  │  │  ├─ MCP2515.c       # MCP2515 driver
│  │  │  ├─ USART6.c        # ESP8266 AT-command handling
│  │  │  ├─ st7735.c        # TFT display driver
│  │  │  ├─ fonts.c         # Fonts used by TFT
│  │  │  └─ ...             # Optional 16x2 LCD driver, helpers, etc.
│  ├─ IOT_GATEWAY.ioc       # STM32CubeMX configuration
│  └─ .project/.cproject/.settings/
│
└─ IOT_node/      # STM32G030F6Px node project (STM32CubeIDE)
   ├─ Core/
   │  ├─ Src/
   │  │  ├─ main.c          # Node application logic (ADC + CAN)
   │  │  ├─ CANSPI.c        # CAN over MCP2515
   │  │  ├─ MCP2515.c       # MCP2515 driver
   │  │  └─ ...
   ├─ IOT_node.ioc          # STM32CubeMX configuration
   └─ .project/.cproject/.settings/

```

## 3\. Hardware Pinout

### 3.1 IOT\_node (STM32G030F6Px)

| Function | MCU Pin | Port | Notes |
| --- | --- | --- | --- |
| Status switch | PC14 | C | `SWITCH_Pin` |
| Status LED | PC15 | C | `RED_LED_Pin` |
| LM35 analog input (ADC1) | PA0 | A | `LM_35_Pin`, ADC Channel 0 |
| MCP2515 SPI SCK | PA1 | A | `SCK_Pin`, SPI1 SCK |
| MCP2515 chip select (CS) | PA4 | A | `NSS_Pin`, active-low CS |
| Node address DIP A0 | PA5 | A | `DIP_A0_Pin` (LSB) |
| MCP2515 SPI MISO | PA6 | A | `MISO_Pin`, SPI1 MISO |
| MCP2515 SPI MOSI | PA7 | A | `MOSI_Pin`, SPI1 MOSI |
| Node address DIP A1 | PA11 | A | `DIP_A1_Pin` |
| Node address DIP A2 | PA12 | A | `DIP_A2_Pin` (MSB) |

> The node ID `NODE` is computed from the three DIP inputs in firmware. Adjust the DIP switch orientation and pull-ups as needed for your hardware.


### 3.2 IOT\_GATEWAY (STM32F401RBT6)

#### CAN Interface (MCP2515 via SPI2)

| Function | MCU Pin | Port | Notes |
| --- | --- | --- | --- |
| MCP2515 SPI2 MISO | PC2 | C | `MISO_Pin`, SPI2 MISO |
| MCP2515 SPI2 MOSI | PC3 | C | `MOSI_Pin`, SPI2 MOSI |
| MCP2515 chip select (CS) | PC4 | C | `CS_OUT_Pin`, active-low CS |
| MCP2515 SPI2 SCK | PB10 | B | `SCK_Pin`, SPI2 SCK |

_MCP2515 is then connected to a CAN transceiver, which drives CAN\_H / CAN\_L._

#### TFT Display (ST7735 via SPI1)

| Function | MCU Pin | Port | Notes |
| --- | --- | --- | --- |
| TFT D/C (data/command) | PA0 | A | `SPI1_D_C_Pin` |
| TFT Reset | PA1 | A | `SPI1_RST_Pin`, active-low |
| TFT Chip Select | PA4 | A | `SPI1_CS_Pin`, active-low CS |
| TFT SPI1 SCK | PA5 | A | `SPI1_SCK_Pin`, SPI1 SCK |
| TFT SPI1 MOSI | PA7 | A | `SPI1_MOSI_Pin`, SPI1 MOSI |

#### Wi-Fi (ESP8266 via USART6)

| Function | MCU Pin | Port | Notes |
| --- | --- | --- | --- |
| ESP8266 RX | PC6 | C | `USART_TX_Pin` (MCU TX → ESP RX) |
| ESP8266 TX | PC7 | C | `USART_RX_Pin` (MCU RX ← ESP TX) |

#### User Interface (Switches, LEDs, Buzzer, Optional LCD)

| Function | MCU Pin | Port | Notes |
| --- | --- | --- | --- |
| User switch UP | PC8 | C | `SW_UP_Pin` (request from Node 1) |
| User switch DOWN | PC9 | C | `SW_DN_Pin` (request from Node 2) |
| Status LED (red) | PB13 | B | `RED_LED_Pin` |
| Status LED (green) | PB14 | B | `GREEN_LED_Pin` |
| Buzzer | PB12 | B | `BUZZER_Pin` |
| LCD D4 | PB0 | B | `LCD_D4_Pin` (16×2 LCD, optional) |
| LCD D5 | PB1 | B | `LCD_D5_Pin` |
| LCD D6 | PB2 | B | `LCD_D6_Pin` |
| LCD D7 | PB3 | B | `LCD_D7_Pin` |
| LCD RS | PB4 | B | `LCD_RS_Pin` |
| LCD RW | PB5 | B | `LCD_RW_Pin` |
| LCD EN | PB8 | B | `LCD_EN_Pin` |

If your hardware revision uses different pins, update the GPIO / SPI / USART configuration in the `.ioc` files and regenerate code.

* * *

## 4\. Getting Started

### 4.1 Download the Repository

`Download the repository as .zip`  
`Extract the .zip file`   

### 4.2 Open Projects in STM32CubeIDE

1.  Launch **STM32CubeIDE**.
    
2.  Go to **File → Open Projects from File System…**.
    
3.  Select the downloaded repository folder.
    
4.  Import both:
    
    -   `IOT_GATEWAY`
        
    -   `IOT_node`
        

### 4.3 **Important: Generate Code from `.ioc`**

On first import, STM32CubeIDE may be missing some auto-generated HAL files.  
For **each project**:

1.  Double-click the project’s `.ioc` file (e.g. `IOT_GATEWAY.ioc`, `IOT_node.ioc`).
    
2.  CubeMX configuration view will open.
    
3.  Click **Project → Generate Code** (or the gear icon on the toolbar).
    
4.  Wait until code generation completes without errors.
    

>If you skip this step, the projects may **fail to build** due to missing generated sources.  
>You only need to regenerate code again if you change the `.ioc` configuration.  

### 4.4 Build

1.  In the **Project Explorer**, right-click `IOT_node` → **Build Project**.
    
2.  Right-click `IOT_GATEWAY` → **Build Project**.
    

Make sure the selected MCUs are:

-   `IOT_node` → **STM32G030F6Px**
    
-   `IOT_GATEWAY` → **STM32F401RBT6**
    

### 4.5 Flash and Run

1.  Connect each board to your PC using an **ST-Link** debug interface.
    
2.  Select the project you want to program (`IOT_node` or `IOT_GATEWAY`).
    
3.  Click **Run** or **Debug** in STM32CubeIDE.
    
4.  Confirm the debug configuration if prompted, then let STM32CubeIDE program the MCU.
    


## 5\. Operating the Demo

1.  **Prepare the Node**
    
    -   Power the **IOT\_node** board with MCP2515 and LM35 connected.
        
    -   Set the node DIP switches (A0–A2) to select a node ID (e.g. `1` or `2`).
        
2.  **Prepare the Gateway**
    
    -   Power the **IOT\_GATEWAY** board with:
        
        -   MCP2515 connected to the same CAN bus as the node.
            
        -   ESP8266 wired to USART6 (TX/RX + power).
            
        -   ST7735 TFT connected to SPI1.
            
    -   Ensure both MCP2515s are correctly wired to their CAN transceivers and bus termination is present.
        
3.  **Run the System**
    
    -   On the gateway:
        
        -   Press **SW\_UP** → sends a CAN request for Node ID (e.g. `0x01`).
            
        -   Press **SW\_DN** → sends a CAN request for another node ID (e.g. `0x02`).
            
    -   The node receives the request, measures temperature from LM35, and sends a CAN response.
        
    -   The gateway:
        
        -   Parses the received frame.
            
        -   Updates the TFT with the latest temperature for that node.
            
        -   Calls the Wi-Fi task to send an HTTP GET to the configured server through the ESP8266.
            


[![Watch the Demo Video](https://img.youtube.com/vi/mkOGOZv5ZoA/maxresdefault.jpg)](https://www.youtube.com/watch?v=mkOGOZv5ZoA)

> 🎥 Click the image to watch the Smart Weather Monitor System in action!
