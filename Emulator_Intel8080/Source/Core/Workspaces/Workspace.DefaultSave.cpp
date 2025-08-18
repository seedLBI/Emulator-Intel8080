#include "Workspace.DefaultSave.h"

const std::string workspace_default_save = u8R"_WSAVE_(
{
    "Workspaces": {
        "index_choosed": 1,
        "workspaces": [
            {
                "flag_LoadStyle": false,
                "imgui": "[Window][WindowOverViewport_11111111]\nPos=0,68\nSize=1920,1092\nCollapsed=0\n\n[Window][Все цвета]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,0\n\n[Window][Все символы]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,1\n\n[Window][Символьный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,0\n\n[Window][Пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,2\n\n[Window][Продвинутый пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,1\n\n[Window][Окно ввода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x0000000A,2\n\n[Window][Окно вывода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x0000000A,3\n\n[Window][Таймер]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x0000000A,1\n\n[Window][Редактор кода]\nPos=0,68\nSize=732,689\nCollapsed=0\nDockId=0x00000003,0\n\n[Window][Мнемо код]\nPos=1256,68\nSize=664,546\nCollapsed=0\nDockId=0x00000009,0\n\n[Window][Регистры и флаги]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x0000000A,0\n\n[Window][Маркеры]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Переменные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,2\n\n[Window][Постоянные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,1\n\n[Window][Быстродействие]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Debug##Default]\nPos=60,43\nSize=400,400\nCollapsed=0\n\n[Window][Настройки]\nPos=320,216\nSize=1280,728\nCollapsed=0\n\n[Window][Создание рабочего пространства]\nPos=720,484\nSize=480,192\nCollapsed=0\n\n[Docking][Data]\nDockSpace       ID=0x7C6B3D9B Window=0xA87D555D Pos=0,68 Size=1920,1092 Split=X\n  DockNode      ID=0x00000007 Parent=0x7C6B3D9B SizeRef=1254,1092 Split=X\n    DockNode    ID=0x00000001 Parent=0x00000007 SizeRef=732,1092 Split=Y Selected=0x2996B9AD\n      DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=732,689 Selected=0x2996B9AD\n      DockNode  ID=0x00000004 Parent=0x00000001 SizeRef=732,401 Selected=0xC97C99AA\n    DockNode    ID=0x00000002 Parent=0x00000007 SizeRef=520,1092 Split=Y Selected=0x2E6B7412\n      DockNode  ID=0x00000005 Parent=0x00000002 SizeRef=1186,554 Selected=0x16A5F508\n      DockNode  ID=0x00000006 Parent=0x00000002 SizeRef=1186,536 CentralNode=1 Selected=0x2E6B7412\n  DockNode      ID=0x00000008 Parent=0x7C6B3D9B SizeRef=664,1092 Split=Y Selected=0x82F0852A\n    DockNode    ID=0x00000009 Parent=0x00000008 SizeRef=664,546 Selected=0x82F0852A\n    DockNode    ID=0x0000000A Parent=0x00000008 SizeRef=664,544 Selected=0x5D79DED8\n\n",
                "name": "Всё и сразу",
                "widgets": {
                    "Быстродействие": {
                        "flag_Active": true,
                        "flag_Show": false
                    },
                    "Все символы": {
                        "flag_Active": true,
                        "flag_Show": true
                    },
                    "Все цвета": {
                        "flag_Active": false,
                        "flag_Show": true
                    },
                    "История выполнения": {
                        "flag_Active": false,
                        "flag_Show": false
                    },
                    "Клавиатура": {
                        "flag_Active": false,
                        "flag_Show": false
                    },
                    "Маркеры": {
                        "flag_Active": false,
                        "flag_Show": true
                    },
                    "Мнемо код": {
                        "flag_Active": true,
                        "flag_Show": true
                    },
                    "Мнемо код (нацеленный)": {
    "Target": "PC",
        "flag_Active" : false,
        "flag_Show" : false
},
"Окно ввода" : {
    "flag_Active": false,
        "flag_Show" : true
},
"Окно вывода" : {
    "Bin_enable": false,
        "Char_enable" : false,
        "Dec_enable" : true,
        "Hex_enable" : false,
        "flag_Active" : false,
        "flag_Show" : true,
        "mode_output" : true
},
"Переменные": {
    "flag_Active": true,
        "flag_Show" : true
},
"Пиксельный экран" : {
    "DrawGrid": false,
        "Line" : {
        "color": {
            "alpha": 0.20000000298023224,
                "blue" : 0.0,
                "green" : 0.0,
                "red" : 0.0
        },
            "thikness": 1
    },
        "Ratio_Mode": 0,
        "flag_Active" : true,
        "flag_Show" : true
},
"Постоянные": {
    "flag_Active": false,
        "flag_Show" : true
},
"Продвинутый пиксельный экран" : {
    "DrawFrontBuffer": 1,
        "DrawGrid" : false,
        "Line" : {
        "color": {
            "alpha": 0.20000000298023224,
                "blue" : 0.0,
                "green" : 0.0,
                "red" : 0.0
        },
            "thikness": 1
    },
        "Ratio_Mode": 0,
        "flag_Active" : false,
        "flag_Show" : true
},
"Просмотр памяти": {
    "flag_Active": false,
        "flag_Show" : false
},
"Регистры и флаги" : {
    "flag_Active": true,
        "flag_Show" : true
},
"Редактор кода" : {
    "flag_Active": true,
        "flag_Show" : true
},
"Руководство" : {
    "flag_Active": false,
        "flag_EnableWrapedText" : true,
        "flag_Show" : false
},
"Символьный экран" : {
    "DrawGrid": true,
        "Line" : {
        "color": {
            "alpha": 0.30000001192092896,
                "blue" : 1.0,
                "green" : 1.0,
                "red" : 1.0
        },
            "thikness": 1
    },
        "Ratio_Mode": 0,
        "flag_Active" : false,
        "flag_Show" : true
},
"Таблица инструкций": {
    "flag_Active": false,
        "flag_Show" : false
},
"Таймер" : {
    "flag_Active": false,
        "flag_Show" : true
}

)_WSAVE_"
u8R"_WSAVE_(

                }
            },
            {
                "flag_LoadStyle": false,
                "imgui" : "[Window][WindowOverViewport_11111111]\nPos=0,68\nSize=1920,1092\nCollapsed=0\n\n[Window][Все цвета]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,0\n\n[Window][Все символы]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,1\n\n[Window][Символьный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,0\n\n[Window][Пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,2\n\n[Window][Продвинутый пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,1\n\n[Window][Окно ввода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,2\n\n[Window][Окно вывода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,3\n\n[Window][Таймер]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,1\n\n[Window][Редактор кода]\nPos=0,68\nSize=980,546\nCollapsed=0\nDockId=0x00000009,0\n\n[Window][Мнемо код]\nPos=0,616\nSize=980,544\nCollapsed=0\nDockId=0x0000000A,0\n\n[Window][Регистры и флаги]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,0\n\n[Window][Маркеры]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Переменные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,2\n\n[Window][Постоянные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,1\n\n[Window][Быстродействие]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Debug##Default]\nPos=60,43\nSize=400,400\nCollapsed=0\n\n[Window][Настройки]\nPos=320,216\nSize=1280,728\nCollapsed=0\n\n[Window][Создание рабочего пространства]\nPos=720,484\nSize=480,192\nCollapsed=0\n\n[Window][Руководство]\nPos=982,68\nSize=938,1092\nCollapsed=0\nDockId=0x00000006,0\n\n[Window][Таблица инструкций]\nPos=0,68\nSize=1728,982\nCollapsed=0\n\n[Docking][Data]\nDockSpace         ID=0x7C6B3D9B Window=0xA87D555D Pos=0,68 Size=1920,1092 Split=X\n  DockNode        ID=0x00000007 Parent=0x7C6B3D9B SizeRef=1254,1092 Split=X\n    DockNode      ID=0x00000001 Parent=0x00000007 SizeRef=980,1092 Split=Y Selected=0x2996B9AD\n      DockNode    ID=0x00000003 Parent=0x00000001 SizeRef=732,689 Split=Y Selected=0x2996B9AD\n        DockNode  ID=0x00000009 Parent=0x00000003 SizeRef=732,546 Selected=0x2996B9AD\n        DockNode  ID=0x0000000A Parent=0x00000003 SizeRef=732,544 Selected=0x82F0852A\n      DockNode    ID=0x00000004 Parent=0x00000001 SizeRef=732,401 Selected=0xC97C99AA\n    DockNode      ID=0x00000002 Parent=0x00000007 SizeRef=938,1092 Split=Y Selected=0x2E6B7412\n      DockNode    ID=0x00000005 Parent=0x00000002 SizeRef=1186,554 Selected=0x16A5F508\n      DockNode    ID=0x00000006 Parent=0x00000002 SizeRef=1186,536 CentralNode=1 Selected=0x98FFBC6D\n  DockNode        ID=0x00000008 Parent=0x7C6B3D9B SizeRef=664,1092 Selected=0x5D79DED8\n\n",
                "name" : "Минимум",
)_WSAVE_"
u8R"_WSAVE_(
                "widgets" : {
                    "Быстродействие": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Все символы" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Все цвета" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "История выполнения" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Клавиатура" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Маркеры" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Мнемо код" : {
                        "flag_Active": true,
                        "flag_Show" : true
                    },
                    "Мнемо код (нацеленный)" : {
                        "Target": "PC",
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Окно ввода" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Окно вывода" : {
                        "Bin_enable": false,
                        "Char_enable" : false,
                        "Dec_enable" : true,
                        "Hex_enable" : false,
                        "flag_Active" : false,
                        "flag_Show" : false,
                        "mode_output" : true
                    },
                    "Переменные": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Пиксельный экран" : {
                        "DrawGrid": false,
                        "Line" : {
                            "color": {
                                "alpha": 0.20000000298023224,
                                "blue" : 0.0,
                                "green" : 0.0,
                                "red" : 0.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Постоянные": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Продвинутый пиксельный экран" : {
                        "DrawFrontBuffer": 1,
                        "DrawGrid" : false,
                        "Line" : {
                            "color": {
                                "alpha": 0.20000000298023224,
                                "blue" : 0.0,
                                "green" : 0.0,
                                "red" : 0.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Просмотр памяти": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Регистры и флаги" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Редактор кода" : {
                        "flag_Active": true,
                        "flag_Show" : true
                    },
                    "Руководство" : {
                        "flag_Active": true,
                        "flag_EnableWrapedText" : true,
                        "flag_Show" : true
                    },
                    "Символьный экран" : {
                        "DrawGrid": true,
                        "Line" : {
                            "color": {
                                "alpha": 0.30000001192092896,
                                "blue" : 1.0,
                                "green" : 1.0,
                                "red" : 1.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Таблица инструкций": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Таймер" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    }
                }
            },
)_WSAVE_"
u8R"_WSAVE_(
            {
                "flag_LoadStyle": false,
                "imgui" : "[Window][WindowOverViewport_11111111]Pos=0,68\nSize=1920,1092\nCollapsed=0\n\n[Window][Все цвета]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,0\n\n[Window][Все символы]\nPos=734,624\nSize=520,536\nCollapsed=0\nDockId=0x00000006,1\n\n[Window][Символьный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,0\n\n[Window][Пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,2\n\n[Window][Продвинутый пиксельный экран]\nPos=734,68\nSize=520,554\nCollapsed=0\nDockId=0x00000005,1\n\n[Window][Окно ввода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,2\n\n[Window][Окно вывода]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,3\n\n[Window][Таймер]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,1\n\n[Window][Редактор кода]\nPos=0,68\nSize=980,546\nCollapsed=0\nDockId=0x00000009,0\n\n[Window][Мнемо код]\nPos=0,616\nSize=980,544\nCollapsed=0\nDockId=0x0000000A,0\n\n[Window][Регистры и флаги]\nPos=1256,616\nSize=664,544\nCollapsed=0\nDockId=0x00000008,0\n\n[Window][Маркеры]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Переменные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,2\n\n[Window][Постоянные]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,1\n\n[Window][Быстродействие]\nPos=0,759\nSize=732,401\nCollapsed=0\nDockId=0x00000004,0\n\n[Window][Debug##Default]\nPos=60,43\nSize=400,400\nCollapsed=0\n\n[Window][Настройки]\nPos=320,216\nSize=1280,728\nCollapsed=0\n\n[Window][Создание рабочего пространства]\nPos=720,484\nSize=480,192\nCollapsed=0\n\n[Window][Руководство]\nPos=982,68\nSize=938,1092\nCollapsed=0\nDockId=0x00000006,0\n\n[Window][Таблица инструкций]\nPos=0,68\nSize=1920,1092\nCollapsed=0\nDockId=0x00000006,0\n\n[Docking][Data]\nDockSpace         ID=0x7C6B3D9B Window=0xA87D555D Pos=0,68 Size=1920,1092 Split=X\n  DockNode        ID=0x00000007 Parent=0x7C6B3D9B SizeRef=1254,1092 Split=X\n    DockNode      ID=0x00000001 Parent=0x00000007 SizeRef=980,1092 Split=Y Selected=0x2996B9AD\n      DockNode    ID=0x00000003 Parent=0x00000001 SizeRef=732,689 Split=Y Selected=0x2996B9AD\n        DockNode  ID=0x00000009 Parent=0x00000003 SizeRef=732,546 Selected=0x2996B9AD\n        DockNode  ID=0x0000000A Parent=0x00000003 SizeRef=732,544 Selected=0x82F0852A\n      DockNode    ID=0x00000004 Parent=0x00000001 SizeRef=732,401 Selected=0xC97C99AA\n    DockNode      ID=0x00000002 Parent=0x00000007 SizeRef=938,1092 Split=Y Selected=0x2E6B7412\n      DockNode    ID=0x00000005 Parent=0x00000002 SizeRef=1186,554 Selected=0x16A5F508\n      DockNode    ID=0x00000006 Parent=0x00000002 SizeRef=1186,536 CentralNode=1 Selected=0xE334999E\n  DockNode        ID=0x00000008 Parent=0x7C6B3D9B SizeRef=664,1092 Selected=0x82F0852A\n\n",
                "name" : "Таблица",
                "widgets" : {
                    "Быстродействие": {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Все символы" : {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Все цвета" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "История выполнения" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Клавиатура" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Маркеры" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Мнемо код" : {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Мнемо код (нацеленный)" : {
                        "Target": "PC",
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Окно ввода" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Окно вывода" : {
                        "Bin_enable": false,
                        "Char_enable" : false,
                        "Dec_enable" : true,
                        "Hex_enable" : false,
                        "flag_Active" : false,
                        "flag_Show" : false,
                        "mode_output" : true
                    },
                    "Переменные": {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Пиксельный экран" : {
                        "DrawGrid": false,
                        "Line" : {
                            "color": {
                                "alpha": 0.20000000298023224,
                                "blue" : 0.0,
                                "green" : 0.0,
                                "red" : 0.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : true,
                        "flag_Show" : false
                    },
                    "Постоянные": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
)_WSAVE_"
u8R"_WSAVE_(
                    "Продвинутый пиксельный экран" : {
                        "DrawFrontBuffer": 1,
                        "DrawGrid" : false,
                        "Line" : {
                            "color": {
                                "alpha": 0.20000000298023224,
                                "blue" : 0.0,
                                "green" : 0.0,
                                "red" : 0.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Просмотр памяти": {
                        "flag_Active": false,
                        "flag_Show" : false
                    },
                    "Регистры и флаги" : {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Редактор кода" : {
                        "flag_Active": true,
                        "flag_Show" : false
                    },
                    "Руководство" : {
                        "flag_Active": true,
                        "flag_EnableWrapedText" : true,
                        "flag_Show" : false
                    },
                    "Символьный экран" : {
                        "DrawGrid": true,
                        "Line" : {
                            "color": {
                                "alpha": 0.30000001192092896,
                                "blue" : 1.0,
                                "green" : 1.0,
                                "red" : 1.0
                            },
                            "thikness": 1
                        },
                        "Ratio_Mode": 0,
                        "flag_Active" : false,
                        "flag_Show" : false
                    },
                    "Таблица инструкций": {
                        "flag_Active": true,
                        "flag_Show" : true
                    },
                    "Таймер" : {
                        "flag_Active": false,
                        "flag_Show" : false
                    }
                }
            }
        ]
    }
}

)_WSAVE_";