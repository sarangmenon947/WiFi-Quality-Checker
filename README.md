# ESP8266 Wi-Fi Quality Checker

A lightweight Arduino/ESP8266 project that measures Wi-Fi connection quality at startup, indicates the result via LEDs, and serves a live status page over HTTP.

---

## How It Works

On boot, the ESP8266 attempts to connect to Wi-Fi and measures how long the connection takes. That duration is used as a proxy for signal quality:

| Connection Time | Signal Quality | LED Indicator |
|----------------|----------------|---------------|
| ≤ 5 seconds    | Excellent       | LED 1 (D0) ON |
| ≤ 10 seconds   | Good            | LED 2 (D1) ON |
| > 10 seconds   | Poor            | LED 3 (D2) ON |
| > 20 seconds   | Failed          | No LED / halts |

Once connected, a web server starts on port **80**. Visiting the device's IP in a browser shows a simple HTML page with the current connection quality.

---

## Hardware Requirements

- ESP8266 board (e.g. NodeMCU, Wemos D1 Mini)
- 3 LEDs with appropriate current-limiting resistors (~220Ω)
- Connections:

| LED   | Pin |
|-------|-----|
| LED 1 | D0  |
| LED 2 | D1  |
| LED 3 | D2  |

---

## Project Structure

```
├── main.ino          # Main sketch
└── credentials.h     # Wi-Fi credentials (not committed to version control)
```

### credentials.h

Create this file in the same directory as your sketch:

```cpp
#define WIFI_SSID     "your_network_name"
#define WIFI_PASSWORD "your_password"
```

---

## Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) with the ESP8266 board package installed
- Add the ESP8266 board manager URL under **File → Preferences → Additional Board Manager URLs**:
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```

### Flash Instructions

1. Clone or download this repository.
2. Create `credentials.h` with your Wi-Fi credentials (see above).
3. Open `main.ino` in the Arduino IDE.
4. Select your board under **Tools → Board → ESP8266 Boards**.
5. Select the correct port under **Tools → Port**.
6. Click **Upload**.

---

## Usage

1. Open the **Serial Monitor** at **115200 baud** to watch the connection progress:
   ```
   Connecting to Wi-Fi......
   Connected to Wi-Fi!
   Time taken: 3200 ms
   Server started
   IP address: 192.168.1.42
   ```
2. Navigate to the printed IP address in any browser on the same network:
   ```
   http://192.168.1.42
   ```
3. The page displays the detected signal quality.

---

## Code Structure

| Function / Section | Description |
|--------------------|-------------|
| `setup()`          | Connects to Wi-Fi, measures connection time, lights the appropriate LED, starts the HTTP server |
| `loop()`           | Listens for incoming HTTP clients and serves the signal quality status page |
| `credentials.h`    | Stores SSID and password as macros, kept outside source control |
