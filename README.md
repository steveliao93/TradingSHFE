# C++ Qt Trading System for SHFE

A professional trading software developed in C++ with Qt framework for Shanghai Futures Exchange (SHFE) connectivity. This system provides real-time market data, order management, and trading capabilities through a modern Qt GUI interface.

## Overview

This trading system is designed to connect directly to SHFE (Shanghai Futures Exchange) servers using the CTP (Comprehensive Transaction Platform) API. The application provides a complete trading solution with authentication, market data subscription, order placement, and position management.

## Features

- **SHFE Server Integration**: Direct connectivity to Shanghai Futures Exchange
- **User Authentication**: Secure login with broker authentication
- **Real-time Market Data**: Live price feeds and market depth information
- **Order Management**: Place, modify, and cancel trading orders
- **Position Tracking**: Real-time position and P&L monitoring
- **Multi-server Support**: Configurable server endpoints for production and testing
- **SQLite Integration**: Local data persistence for market data and trading records
- **Modern Qt GUI**: Professional trading interface with real-time updates

## Architecture

### Core Components

| Component | File | Description |
|-----------|------|-------------|
| **Main Application** | `main.cpp` | Application entry point and initialization |
| **Login System** | `logindialog.cpp/h` | User authentication with SHFE servers |
| **Main Window** | `loginmain.cpp/h` | Primary application window and menu system |
| **Market Data Display** | `mdquota.cpp/h` | Real-time market data visualization |
| **Trading API** | `traderapi.cpp/h` | CTP Trading API wrapper |
| **Market Data API** | `mdapi.cpp/h` | CTP Market Data API wrapper |
| **Trading SPI** | `traderspi.cpp/h` | Trading event callbacks |
| **Market Data SPI** | `mdspi.cpp/h` | Market data event callbacks |
| **Database Operations** | `SqliteOperator.*` | SQLite database integration |

### API Integration

The system integrates with SHFE's CTP (Comprehensive Transaction Platform) API:

- **ThostFtdcTraderApi.h**: Trading operations interface
- **ThostFtdcMdApi.h**: Market data subscription interface
- **ThostFtdcUserApiStruct.h**: Data structure definitions
- **ThostFtdcUserApiDataType.h**: Data type definitions

### GUI Components

Built with Qt framework providing:

- **Login Dialog** (`logindialog.ui`): Server selection and authentication
- **Main Window** (`loginmain.ui`): Application control center
- **Market Data Widget** (`mdquota.ui`): Real-time price display and trading controls
- **Data Management** (`dataload.ui`): Data loading and management
- **Quote Lists** (`quotalist.ui`): Instrument subscription management

## Project Structure

```
LoginDialog/
├── source/                    # C++ source files
│   ├── main.cpp              # Application entry point
│   ├── logindialog.cpp       # Login dialog implementation
│   ├── loginmain.cpp         # Main window implementation
│   ├── mdquota.cpp           # Market data widget
│   ├── traderapi.cpp         # Trading API wrapper
│   ├── traderspi.cpp         # Trading callbacks
│   ├── mdapi.cpp             # Market data API wrapper
│   ├── mdspi.cpp             # Market data callbacks
│   └── ...
├── hearder/                  # Header files
│   ├── main.h
│   ├── logindialog.h
│   ├── ThostFtdcTraderApi.h  # CTP Trading API
│   ├── ThostFtdcMdApi.h      # CTP Market Data API
│   └── ...
├── qt/                       # Qt UI files and project
│   ├── LoginDialog.pro       # Qt project file
│   ├── logindialog.ui        # Login dialog UI
│   ├── loginmain.ui          # Main window UI
│   ├── mdquota.ui            # Market data widget UI
│   └── ...
├── flow/                     # CTP API flow files
├── x64/                      # Build output directory
│   ├── Debug/
│   └── Release/
├── thosttraderapi_se.dll     # CTP Trading API library
├── thostmduserapi_se.dll     # CTP Market Data API library
└── test.db                   # SQLite database file
```

## Building and Compilation

### Prerequisites

1. **Development Environment**:
   - Visual Studio 2019 or later
   - Qt 6.x framework
   - Qt Visual Studio Tools extension

2. **CTP API Libraries**:
   - `thosttraderapi_se.dll` - Trading API
   - `thostmduserapi_se.dll` - Market Data API
   - `thosttraderapi_se.lib` - Trading API import library
   - `thostmduserapi_se.lib` - Market Data API import library

### Build Steps

1. **Open Project**:
   ```bash
   # Open in Visual Studio
   LoginDialog.sln
   
   # Or use Qt Creator
   qt/LoginDialog.pro
   ```

2. **Configure Dependencies**:
   - Ensure Qt6 is properly installed and configured
   - Verify CTP API libraries are in the project directory
   - Set up include paths for Qt and CTP headers

3. **Build Configuration**:
   - Debug: For development and testing
   - Release: For production deployment

4. **Compile**:
   ```bash
   # Using Visual Studio
   Build -> Build Solution (Ctrl+Shift+B)
   
   # Using Qt Creator
   Build -> Build All (Ctrl+B)
   ```

## Configuration

### Server Settings

The application supports multiple SHFE server configurations:

```cpp
// Server Configuration in logindialog.cpp
if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "1") == 0) {
    // Primary Server
    m_tradeApi->RegisterFront("tcp://180.166.12.248:42205");
    m_cmapi->RegisterFront("tcp://180.166.12.248:42213");
}
else if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "2") == 0) {
    // Secondary Server  
    m_tradeApi->RegisterFront("tcp://101.230.185.213:43205");
    m_cmapi->RegisterFront("tcp://101.230.185.213:43213");
}
else if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "3") == 0) {
    // Local Testing Server
    m_tradeApi->RegisterFront("tcp://127.0.0.1:41205");
    m_cmapi->RegisterFront("tcp://127.0.0.1:41213");
}
```

### Authentication Parameters

Default authentication settings:

```cpp
// In logindialog.cpp - Userauth() function
strcpy_s(ReqAuthentLogin.BrokerID, "4020");
strcpy_s(ReqAuthentLogin.AuthCode, "L6HTO9EXQ83ASX36");  
strcpy_s(ReqAuthentLogin.AppID, "client_family_1.1");
```

## Usage

### Starting the Application

1. **Launch**: Run `LoginDialog.exe` from the build output directory
2. **Server Selection**: Choose appropriate server (1, 2, or 3)
3. **Authentication**: Enter your SHFE credentials
4. **Login**: Click login to establish connection

### Trading Operations

1. **Market Data**: 
   - Access through main window → Trading menu
   - Subscribe to instruments (e.g., au2412, ag2412)
   - View real-time price updates in the mdquota window

2. **Order Placement**:
   - Use the trading controls in the market data widget
   - Configure buy/sell parameters
   - Monitor order status and executions

3. **Position Management**:
   - View current positions in the interface
   - Monitor profit/loss calculations
   - Track account balance and margin

### Key Features in GUI

#### Login Dialog (`logindialog.ui`)
- User ID input field
- Password input (masked)
- Server selection dropdown
- Status display area
- Login button

#### Main Window (`loginmain.ui`)
- Menu system (System, Trading)
- Login button
- Trading functionality access
- Status information

#### Market Data Widget (`mdquota.ui`)
- Real-time price display
- Time display
- Trading controls (Buy/Sell)
- Volume configuration
- Profit display
- Market data table

## Database Integration

The system uses SQLite for local data persistence:

```cpp
// Database operations handled in SqliteOperator class
// - Market data storage
// - Order history
// - Trade records
// - Position snapshots
```

## Error Handling and Logging

The system includes comprehensive error handling:

- **Connection Failures**: Automatic retry mechanisms
- **Authentication Errors**: Clear error messaging
- **API Responses**: Detailed error code handling
- **GUI Feedback**: Real-time status updates

## API Event Handling

### Trading Events
```cpp
// Key callback methods in traderspi.cpp
void OnFrontConnected();                    // Server connection established
void OnRspAuthenticate(...);               // Authentication response  
void OnRspUserLogin(...);                  // Login response
void OnRspOrderInsert(...);                // Order submission response
void OnRtnTrade(...);                      // Trade execution notification
```

### Market Data Events
```cpp
// Key callback methods in mdspi.cpp  
void OnFrontConnected();                   // Market data server connected
void OnRspUserLogin(...);                 // Market data login response
void OnRspSubMarketData(...);             // Subscription response
void OnRtnDepthMarketData(...);           // Real-time market data update
```

## Threading and Concurrency

The application handles multiple concurrent operations:

- **GUI Thread**: User interface updates
- **API Threads**: CTP API callbacks and network operations
- **Database Thread**: Asynchronous data persistence
- **Timer Updates**: Real-time display refreshes

## Deployment

### Distribution Package

For deployment, include:

```
LoginDialog.exe                 # Main executable
Qt6Core.dll                    # Qt runtime libraries  
Qt6Gui.dll
Qt6Widgets.dll
thosttraderapi_se.dll          # CTP API libraries
thostmduserapi_se.dll
platforms/                    # Qt platform plugins
  qwindows.dll
flow/                         # CTP flow directory (created automatically)
```

### System Requirements

- **Operating System**: Windows 10 or later
- **Architecture**: x64
- **Runtime**: Visual C++ Redistributable 2019 or later
- **Network**: Internet connection for SHFE server access
- **Permissions**: Administrator rights for initial setup

## Troubleshooting

### Common Issues

1. **Connection Failures**:
   - Verify network connectivity
   - Check server addresses and ports
   - Ensure firewall allows connections

2. **Authentication Errors**:
   - Verify credentials with broker
   - Check BrokerID and AuthCode settings
   - Ensure account is active and authorized

3. **Market Data Issues**:
   - Confirm market data subscription permissions
   - Check instrument symbols and exchange codes
   - Verify trading session times

4. **Performance Issues**:
   - Monitor CPU and memory usage
   - Check database file size and location
   - Optimize UI refresh rates if needed

### Log Files

The system generates log files in:
- **Flow Directory**: CTP API logs
- **Application Logs**: Custom logging (if implemented)
- **Database**: Error and event logging in SQLite

## Security Considerations

- **Credentials**: Never hardcode production credentials
- **Network**: Use secure connections (CTP handles encryption)
- **Data**: Protect local database files
- **Access**: Implement proper user access controls
- **Updates**: Regularly update CTP API libraries

## Development and Customization

### Adding New Features

1. **Market Data Enhancements**:
   - Modify `mdquota.cpp` for display changes
   - Update `mdspi.cpp` for new data handling
   - Extend database schema in `SqliteOperator`

2. **Trading Features**:
   - Enhance `traderapi.cpp` for new order types
   - Update `traderspi.cpp` for additional callbacks
   - Modify GUI forms as needed

3. **Database Extensions**:
   - Add new tables in SQLite schema
   - Implement corresponding CRUD operations
   - Update data models for GUI display

### Code Standards

- Follow Qt coding conventions
- Use RAII for resource management
- Implement proper error handling
- Document public interfaces
- Use version control for changes

## Migration to Python

A complete Python migration of this C++ system is available in the `python_trading_system/` directory. The Python version provides:

- Same functionality with modern PyQt6 GUI
- Improved maintainability and deployment
- Enhanced error handling and logging
- Comprehensive test suite

See `python_trading_system/README.md` for Python version details.

## License

This project follows the same license terms as the SHFE CTP API. Contact your broker for specific licensing requirements.

## Support

For technical support:
1. Check this documentation first
2. Review CTP API documentation from SHFE
3. Contact your broker's technical support team
4. Refer to Qt documentation for GUI issues

---

**Note**: This is a professional trading system. Always test thoroughly in a development environment before using with live trading accounts. Trading involves financial risk - use appropriate risk management practices.