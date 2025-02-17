#BSOLUTE_FILENAME=`readlink -e "$0"`
BSOLUTE_FILENAME=`readlink "$0"`
DIRECTORY=`dirname "$0"`
cd $DIRECTORY
cd ../../
rm -R outputs/T-Wristband_LiLyGo
mkdir outputs/T-Wristband_LiLyGo
mkdir outputs/T-Wristband_LiLyGo/cubos

# Generating Arduino project
cat generators/default_settings.ino                                     > outputs/T-Wristband_LiLyGo/cubos/cubos.ino
cat generators/T-Wristband_LiLyGo/T-Wristband_LiLyGo_settings.ino       >> outputs/T-Wristband_LiLyGo/cubos/cubos.ino
cat sdk/cubos.ino >> outputs/T-Wristband_LiLyGo/cubos/cubos.ino         >> outputs/T-Wristband_LiLyGo/cubos/cubos.ino
cat generators/T-Wristband_LiLyGo/T-Wristband_LiLyGo_apps.ino           >> outputs/T-Wristband_LiLyGo/cubos/cubos.ino

# Applications
cp sdk/apps/app_alarm.ino           outputs/T-Wristband_LiLyGo/cubos/     
cp sdk/apps/app_battery.ino         outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_compass.ino         outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_ble_sync.ino        outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_i2c_scanner.ino     outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_settings.ino        outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_test.ino            outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_barometer.ino       outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_clock.ino           outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_filemanager.ino     outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_internet.ino        outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_simplegame.ino      outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_z_menu.ino          outputs/T-Wristband_LiLyGo/cubos/
#cp sdk/apps/app_pedometer_test.ino  outputs/T-Wristband_LiLyGo/cubos/
cp sdk/apps/app_pedometer.ino       outputs/T-Wristband_LiLyGo/cubos/

# Drivers
cp sdk/drivers/driver_battery_T-Wristband_LiLyGo.ino                outputs/T-Wristband_LiLyGo/cubos/     
cp sdk/drivers/driver_display_eTFT_ST7735_T-Wristband_LiLyGo.ino    outputs/T-Wristband_LiLyGo/cubos/    
cp sdk/drivers/driver_ble_sync_esp32.ino                            outputs/T-Wristband_LiLyGo/cubos/      
cp sdk/drivers/driver_controls_T-Wristband_LiLyGo.ino               outputs/T-Wristband_LiLyGo/cubos/     
cp sdk/drivers/driver_rtc_pcf8563.ino                               outputs/T-Wristband_LiLyGo/cubos/     
cp sdk/drivers/driver_cpu_T-Wristband_LiLyGo.ino                    outputs/T-Wristband_LiLyGo/cubos/     
cp sdk/drivers/driver_IMU_MPU9250_T-Wristband_LiLyGo.ino            outputs/T-Wristband_LiLyGo/cubos/     

# Core
cp sdk/core/core_basic.ino              outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_shared_functions.ino   outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_views.ino              outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_display.ino            outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_time.ino               outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_cpu.ino                outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_battery.ino            outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_powersave.ino          outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_background.ino         outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_pedometer.ino          outputs/T-Wristband_LiLyGo/cubos/  
cp sdk/core/core_ble_sync.ino           outputs/T-Wristband_LiLyGo/cubos/  

#external libs
cp external_libs/MPU9250_LiLyGO_T-Wristband/MPU9250.cpp                 outputs/T-Wristband_LiLyGo/cubos/ 
cp external_libs/MPU9250_LiLyGO_T-Wristband/MPU9250.h                   outputs/T-Wristband_LiLyGo/cubos/ 
cp external_libs/MPU9250_LiLyGO_T-Wristband/quaternionFilters.cpp       outputs/T-Wristband_LiLyGo/cubos/ 
cp external_libs/MPU9250_LiLyGO_T-Wristband/quaternionFilters.h         outputs/T-Wristband_LiLyGo/cubos/ 
cp external_libs/MPU9250_LiLyGO_T-Wristband/sensor.h                    outputs/T-Wristband_LiLyGo/cubos/ 

echo Finished