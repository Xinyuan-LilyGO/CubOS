//#define CORE_TOUCH_DEBUG
//#define TOUCH_SCREEN_ENABLE

#ifdef TOUCH_SCREEN_ENABLE
    bool TOUCH_SCREEN_last_isTouching   = false;
    bool TOUCH_SCREEN_isDragging        = false;
    bool TOUCH_SCREEN_isLongPressed     = false;

    int TOUCH_SCREEN_last_x = 0;
    int TOUCH_SCREEN_last_y = 0;

    int TOUCH_SCREEN_touch_start_x = 0;
    int TOUCH_SCREEN_touch_start_y = 0;
    bool CORE_TOUCH_swipeStarted = false;

    int getTOUCH_SCREEN_touch_start_x(){
        return TOUCH_SCREEN_touch_start_x;
    }
    int getTOUCH_SCREEN_touch_start_y(){
        return TOUCH_SCREEN_touch_start_y;
    }

    long TOUCH_SCREEN_touch_start_ms = 0;

    long getTOUCH_SCREEN_touch_start_ms(){
        return TOUCH_SCREEN_touch_start_ms;
    }

    void loop_touchScreenCore(){
        loop_touchScreenDriver();
        
        /*
        #define EVENT_ON_TOUCH_START            0x06
        #define EVENT_ON_TOUCH_RELEASED         0x07
        #define EVENT_ON_TOUCH_CLICK            0x08
        #define EVENT_ON_TOUCH_LONG_PRESS       0x09
        #define EVENT_ON_TOUCH_DRAG             0x0A
        #define EVENT_ON_TOUCH_DOUBLE_CLICK     0x0B
        */

        if(!TOUCH_SCREEN_last_isTouching && getTOUCH_SCREEN_isTouching()){

            TOUCH_SCREEN_last_isTouching = true;
            TOUCH_SCREEN_last_x = getTOUCH_SCREEN_X();
            TOUCH_SCREEN_last_y = getTOUCH_SCREEN_Y();
            TOUCH_SCREEN_touch_start_x = TOUCH_SCREEN_last_x;
            TOUCH_SCREEN_touch_start_y = TOUCH_SCREEN_last_y;
            TOUCH_SCREEN_isDragging = false;
            TOUCH_SCREEN_isLongPressed = false;
            TOUCH_SCREEN_touch_start_ms = millis();

            #ifdef CORE_TOUCH_DEBUG
                debug("Touch start");
            #endif

            
            currentApp->onEvent(EVENT_ON_TOUCH_START, TOUCH_SCREEN_last_x, TOUCH_SCREEN_last_y);
            #ifdef SOFTWARE_KEYBOARD_ENABLE
                core_software_keyboard_onEvent(EVENT_ON_TOUCH_START, TOUCH_SCREEN_last_x, TOUCH_SCREEN_last_y);
            #endif
        }else if(TOUCH_SCREEN_last_isTouching && !getTOUCH_SCREEN_isTouching()){

            TOUCH_SCREEN_last_isTouching = false;
            CORE_TOUCH_swipeStarted = false;

            #ifdef CORE_TOUCH_DEBUG
                debug("Touch released");
            #endif

            
            currentApp->onEvent(EVENT_ON_TOUCH_RELEASED, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
            #ifdef SOFTWARE_KEYBOARD_ENABLE
                core_software_keyboard_onEvent(EVENT_ON_TOUCH_RELEASED, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
            #endif

            if(!TOUCH_SCREEN_isDragging && millis()-TOUCH_SCREEN_touch_start_ms<TOUCH_SCREEN_TIME_MS_FOR_LONG_TOUCH){
                
                #if defined(SOFTWARE_BUTTONS_ENABLE) || defined(SOFTWARE_KEYBOARD_ENABLE)
                    if(core_view_isSoftwareButtons_clicked(getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y())){
                        #ifdef CORE_TOUCH_DEBUG
                            debug("Touch click on software button");
                        #endif    
                    }else{
                        #ifdef CORE_TOUCH_DEBUG
                            debug("Touch click");
                        #endif    
                        currentApp->onEvent(EVENT_ON_TOUCH_CLICK, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                        #ifdef SOFTWARE_KEYBOARD_ENABLE
                            core_software_keyboard_onEvent(EVENT_ON_TOUCH_CLICK, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                        #endif
                    }
                #else
                    #ifdef CORE_TOUCH_DEBUG
                        debug("Touch click");
                    #endif    
                    currentApp->onEvent(EVENT_ON_TOUCH_CLICK, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                    #ifdef SOFTWARE_KEYBOARD_ENABLE
                        core_software_keyboard_onEvent(EVENT_ON_TOUCH_CLICK, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                    #endif
                #endif
                
            }else{
                TOUCH_SCREEN_isDragging = false;
                TOUCH_SCREEN_isLongPressed = false;
            }
            

        }else if(TOUCH_SCREEN_last_isTouching && getTOUCH_SCREEN_isTouching()){

            int dx;
            int dy;

            if(!TOUCH_SCREEN_isDragging){
                dx = getTOUCH_SCREEN_X() - TOUCH_SCREEN_touch_start_x;
                dy = getTOUCH_SCREEN_Y() - TOUCH_SCREEN_touch_start_y;
            }else{
                dx = getTOUCH_SCREEN_X() - TOUCH_SCREEN_last_x;
                dy = getTOUCH_SCREEN_Y() - TOUCH_SCREEN_last_y;
            }

            //TOUCH_SCREEN_DELTA_MOVE_FOR_DRAG
            if( (TOUCH_SCREEN_isDragging) || abs(dx)>TOUCH_SCREEN_DELTA_MOVE_FOR_DRAG || abs(dy)>TOUCH_SCREEN_DELTA_MOVE_FOR_DRAG){
                TOUCH_SCREEN_isDragging = true;
                TOUCH_SCREEN_last_x = getTOUCH_SCREEN_X();
                TOUCH_SCREEN_last_y = getTOUCH_SCREEN_Y();

                #ifdef CORE_TOUCH_DEBUG
                    //debug("Touch drag");
                #endif
                
                currentApp->onEvent(EVENT_ON_TOUCH_DRAG, dx, dy);

                if(!CORE_TOUCH_swipeStarted){
                    if(abs(dx)>TOUCH_SCREEN_DELTA_MOVE_FOR_SWIPE || abs(dy)>TOUCH_SCREEN_DELTA_MOVE_FOR_SWIPE){
                        CORE_TOUCH_swipeStarted = true;
                        if(abs(dx)>abs(dy)){
                            if(dx>0){
                                currentApp->onEvent(EVENT_ON_TOUCH_QUICK_SWIPE_TO_RIGHT, dx, dy);
                                #ifdef CORE_TOUCH_DEBUG
                                    debug("CORE_TOUCH_DEBUG: EVENT_ON_TOUCH_QUICK_SWIPE_TO_RIGHT");
                                #endif
                            }else{
                                currentApp->onEvent(EVENT_ON_TOUCH_QUICK_SWIPE_TO_LEFT, dx, dy);
                                #ifdef CORE_TOUCH_DEBUG
                                    debug("CORE_TOUCH_DEBUG: EVENT_ON_TOUCH_QUICK_SWIPE_TO_LEFT");
                                #endif
                            } 
                        }else{
                            if(dy>0){
                                currentApp->onEvent(EVENT_ON_TOUCH_QUICK_SWIPE_TO_BOTTOM, dx, dy);
                                #ifdef CORE_TOUCH_DEBUG
                                    debug("CORE_TOUCH_DEBUG: EVENT_ON_TOUCH_QUICK_SWIPE_TO_BOTTOM");
                                #endif
                            }else{
                                currentApp->onEvent(EVENT_ON_TOUCH_QUICK_SWIPE_TO_TOP, dx, dy);
                                #ifdef CORE_TOUCH_DEBUG
                                    debug("CORE_TOUCH_DEBUG: EVENT_ON_TOUCH_QUICK_SWIPE_TO_TOP");
                                #endif
                            } 
                        }
                    }
                }

                #ifdef SOFTWARE_KEYBOARD_ENABLE
                    core_software_keyboard_onEvent(EVENT_ON_TOUCH_DRAG, dx, dy);
                #endif

            }else if(!TOUCH_SCREEN_isLongPressed && millis()-TOUCH_SCREEN_touch_start_ms>TOUCH_SCREEN_TIME_MS_FOR_LONG_TOUCH){
                TOUCH_SCREEN_isLongPressed = true;

                #ifdef CORE_TOUCH_DEBUG
                    debug("Touch long press");
                #endif
                
                currentApp->onEvent(EVENT_ON_TOUCH_LONG_PRESS, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                #ifdef SOFTWARE_KEYBOARD_ENABLE
                    core_software_keyboard_onEvent(EVENT_ON_TOUCH_LONG_PRESS, getTOUCH_SCREEN_X(), getTOUCH_SCREEN_Y());
                #endif
            }
            
        } 
    }

#endif
