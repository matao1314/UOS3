#ifndef __ICOS_H
#define __ICOS_H


//256色的图标集,16*16大小.
const u8 icostbl[9][256] = {
    {
        //磁盘图标 0
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0XFF,
        0XFF, 0X92, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0X92, 0X00,
        0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X92, 0X92, 0X00,
        0X92, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0X92, 0X92, 0X00,
        0X92, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0X1C, 0X1C, 0XDB, 0X92, 0X92, 0X00,
        0X92, 0XDB, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X1C, 0X1C, 0XDB, 0X92, 0X92, 0X00,
        0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X92, 0X92, 0X00,
        0X92, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0X92, 0X00, 0X00,
        0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X00, 0X00, 0XFF,
        0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    },
    {
        //文件夹图标 1
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XB0, 0XB0, 0XB0, 0XB0, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XB0, 0XFF, 0XFF, 0XFF, 0XFF, 0XB0, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XB0, 0XFF, 0XFE, 0XFE, 0XFE, 0XFE, 0XFF, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XAC, 0XFF, 0XFF, 0XFF,
        0XB0, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XAC, 0XFF, 0XFF, 0XFF,
        0XB0, 0XFE, 0XFE, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XFF,
        0XB0, 0XF9, 0XB0, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFA, 0XFF, 0XB0, 0X8C,
        0XB0, 0XF9, 0XB0, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XF9, 0XFE, 0XB0, 0X8C,
        0XB0, 0XF9, 0XB0, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XF5, 0XFE, 0XB0, 0X8C,
        0XB0, 0XF9, 0XB0, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XD5, 0XFE, 0XB0, 0X8C,
        0XB0, 0XF9, 0XB0, 0XFE, 0XFD, 0XFD, 0XFD, 0XFD, 0XFD, 0XFD, 0XFD, 0XF9, 0XD5, 0XFE, 0XB0, 0X8C,
        0XB0, 0XF9, 0XB0, 0XFE, 0XF9, 0XF9, 0XF9, 0XF9, 0XF9, 0XF9, 0XF9, 0XF9, 0XD4, 0XFE, 0XB0, 0X8C,
        0XFF, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0XB0, 0X8C,
        0XFF, 0XFF, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0X8C, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    },
    {
        //未知文件图标 2
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XBB, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X0F, 0X97,
        0XBB, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X93,
        0XBB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0XDB, 0XFF, 0XBB, 0X93,
        0XBB, 0XFF, 0XFF, 0XB7, 0XB7, 0XFF, 0XFF, 0X13, 0X57, 0XFF, 0XDB, 0X14, 0X59, 0XFF, 0XBB, 0X93,
        0XBB, 0XFF, 0XFF, 0XB7, 0XDB, 0XFF, 0XFF, 0X57, 0X77, 0XFF, 0XDB, 0X55, 0X7A, 0XFF, 0XBB, 0X93,
        0XBB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XBB, 0XBB, 0XBB, 0X93,
        0XBB, 0XFF, 0XFF, 0XF7, 0XF7, 0XFF, 0XFF, 0XBB, 0XBB, 0XFF, 0XDB, 0XDB, 0XDB, 0XBB, 0XBB, 0X93,
        0XBB, 0XFF, 0XFF, 0XED, 0XF1, 0XFF, 0XBB, 0X0A, 0X4F, 0XFF, 0XDB, 0XF4, 0XD5, 0XBB, 0X9B, 0X93,
        0XBB, 0XFF, 0XFF, 0XF6, 0XF6, 0XFF, 0XBB, 0X53, 0X77, 0XFF, 0XDB, 0XD9, 0XDA, 0XBB, 0X9B, 0X93,
        0XBB, 0XFF, 0XFF, 0XDB, 0XDB, 0XFF, 0XFF, 0XDB, 0XDB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0X9B, 0X93,
        0XBB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0X9B, 0X93,
        0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0X9B, 0X9B, 0X9B, 0X97, 0X97, 0X77, 0X57, 0X93,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    },
    {
        //bin文件图标 3
        0X02, 0X02, 0X02, 0X02, 0X02, 0X02, 0X02, 0X00, 0X00, 0X02, 0X02, 0X02, 0X02, 0X02, 0X02, 0X02,
        0X02, 0X02, 0X02, 0X02, 0X02, 0X00, 0X00, 0XFF, 0XFF, 0X00, 0X00, 0X02, 0X02, 0X02, 0X02, 0X02,
        0X02, 0X02, 0X02, 0X02, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X02, 0X02, 0X02, 0X02,
        0X02, 0X03, 0X02, 0X02, 0X1F, 0X00, 0X00, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X03, 0X03, 0X03, 0X02,
        0X03, 0X02, 0X03, 0X03, 0X1F, 0X1F, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X03, 0X02, 0X03, 0X03,
        0X03, 0X03, 0X03, 0X03, 0X1F, 0X00, 0X1F, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X03, 0X03, 0X02, 0X03,
        0X03, 0X03, 0X03, 0X03, 0X1F, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X03, 0X03, 0X03, 0X02,
        0X03, 0X03, 0X03, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X03, 0X03,
        0X03, 0X00, 0X00, 0XFF, 0XFF, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0X00, 0X00, 0X03,
        0X1F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00,
        0X1F, 0X1F, 0X1F, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X1F, 0X1F, 0X1F, 0XFF, 0XFF, 0X00, 0X00, 0X00,
        0X1F, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00,
        0X1F, 0X1F, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X1F, 0X00, 0X00, 0X00, 0X00, 0X00,
        0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF,
    },
    {
        //歌词文件图标 4
        0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X92, 0XFF,
        0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X92, 0XFF,
        0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X92, 0XFF,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X00,
        0X00, 0XFF, 0X80, 0X80, 0X80, 0X80, 0XFF, 0XFF, 0XFF, 0X80, 0X80, 0X80, 0XFF, 0XFF, 0XFF, 0X00,
        0X00, 0XFF, 0X80, 0X80, 0X80, 0X80, 0XFF, 0X80, 0X80, 0XFF, 0X80, 0XFF, 0X80, 0X80, 0X80, 0X00,
        0X00, 0XFF, 0X80, 0X80, 0X80, 0X80, 0XFF, 0XFF, 0XFF, 0X80, 0X80, 0XFF, 0X80, 0X80, 0X80, 0X00,
        0X00, 0XFF, 0X80, 0X80, 0X80, 0X80, 0XFF, 0X80, 0X80, 0XFF, 0X80, 0XFF, 0X80, 0X80, 0X80, 0X00,
        0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0XFF, 0X80, 0X80, 0XFF, 0X80, 0X80, 0XFF, 0XFF, 0XFF, 0X00,
        0X00, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92, 0X92,
        0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X92, 0XFF,
        0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X92, 0XFF,
        0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X92, 0XFF,
    },
    {
        //游戏图标 5
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0X6E, 0X6E, 0X6E, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X6E, 0X6E, 0X6E, 0XFF, 0XFF,
        0XFF, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0XFF,
        0XFF, 0X6E, 0XDB, 0XFF, 0XDB, 0XB7, 0XDB, 0XFF, 0XFF, 0XDB, 0XB7, 0XDB, 0XFF, 0XDB, 0X6E, 0XFF,
        0X6E, 0XDB, 0XFF, 0XE0, 0XFF, 0XDB, 0XB7, 0XFF, 0XFF, 0XB7, 0XDB, 0XFF, 0X08, 0XFF, 0XDB, 0X6E,
        0X6E, 0XFF, 0XE0, 0XFF, 0XE0, 0XFF, 0XB7, 0XFF, 0XFF, 0XB7, 0XFF, 0X61, 0XFF, 0X60, 0XFF, 0X6E,
        0X6E, 0XDB, 0XFF, 0XE0, 0XFF, 0XDB, 0XB7, 0XFF, 0XFF, 0XB7, 0XDB, 0XFF, 0X01, 0XFF, 0XDB, 0X6E,
        0X6E, 0X6E, 0XDB, 0XFF, 0XDB, 0XB7, 0X00, 0XFF, 0XFF, 0X00, 0XB7, 0XDB, 0XFF, 0XDB, 0X6E, 0X6E,
        0X6E, 0XFF, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0X6E, 0XFF, 0X6E,
        0X6E, 0XFF, 0XFF, 0XFF, 0X6E, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X6E, 0XFF, 0XFF, 0XFF, 0X6E,
        0X6E, 0XFF, 0XFF, 0XDB, 0X6E, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X6E, 0XDB, 0XFF, 0XFF, 0X6E,
        0X6E, 0XFF, 0XFF, 0X6E, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X6E, 0XFF, 0XFF, 0X6E,
        0X6E, 0XFF, 0XDB, 0X6E, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X6E, 0XDB, 0XFF, 0X6E,
        0X6E, 0XDB, 0X6E, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X6E, 0XDB, 0X6E,
        0XDB, 0X6E, 0X6E, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X6E, 0X6E, 0XDB,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    },
    {
        //文本文件图标 6
        0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0X92, 0XFF, 0X92, 0XFF, 0X92, 0XFF, 0X92, 0XFF, 0X00, 0XFF, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0X92, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0XDB, 0X00, 0XFF,
        0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF,
    },
    {
        //音乐图标 7
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XB6, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XB6, 0X49, 0X49, 0XDB, 0XFF, 0XFF, 0XB6, 0X92, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XB6, 0X49, 0XFF, 0XFF, 0X49, 0XB6, 0X49, 0XB1, 0X6D, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XB6, 0X49, 0XFF, 0XFF, 0XFF, 0X6D, 0X8D, 0XF5, 0XD0, 0X6E, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XB6, 0X49, 0XFF, 0XFF, 0X92, 0X6D, 0XFA, 0XF5, 0XD0, 0X49, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XB6, 0X49, 0XFF, 0XB6, 0X69, 0XD6, 0XFE, 0XF5, 0XD0, 0X69, 0X49, 0XDB, 0XFF, 0XFF,
        0XFF, 0XB6, 0X49, 0XDB, 0X69, 0XB1, 0XFE, 0XFF, 0XFF, 0XFE, 0XB6, 0X45, 0XFF, 0X49, 0XDB, 0XFF,
        0XB6, 0X49, 0XFF, 0XB6, 0XD1, 0XF5, 0XF5, 0XFE, 0XFE, 0XFA, 0XF5, 0X68, 0XFF, 0XFF, 0X49, 0XDB,
        0XDB, 0X49, 0XFF, 0XB6, 0XAC, 0XF0, 0XFE, 0XFE, 0XF5, 0XF4, 0XF0, 0X44, 0XFF, 0XFF, 0X49, 0XDB,
        0XFF, 0XDB, 0X49, 0XDB, 0X25, 0XD6, 0XF9, 0XF5, 0XF4, 0X8C, 0X6D, 0XFF, 0XFF, 0X49, 0XDB, 0XFF,
        0XFF, 0XFF, 0XDB, 0X44, 0XD5, 0XF5, 0XF4, 0XD0, 0X49, 0XDB, 0XFF, 0XFF, 0X49, 0XDB, 0XFF, 0XFF,
        0XFF, 0XFF, 0X6D, 0XD1, 0XF4, 0XF4, 0X88, 0X6E, 0XFF, 0XFF, 0XFF, 0X49, 0XDB, 0XFF, 0XFF, 0XFF,
        0XFF, 0X92, 0XD0, 0XF4, 0XCC, 0X44, 0XDB, 0XFF, 0XFF, 0XFF, 0X49, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0X92, 0XD0, 0X68, 0X92, 0XDB, 0X49, 0XFF, 0XFF, 0X49, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0X92, 0X49, 0XDB, 0XFF, 0XFF, 0XDB, 0X49, 0X49, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0XDB, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    },
    {
        //图片图标 8
        0XFF, 0XFF, 0X97, 0X97, 0X97, 0X97, 0X97, 0X97, 0X97, 0X97, 0X97, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
        0XFF, 0XFF, 0X97, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X97, 0X77, 0X6E, 0XB6, 0XDF, 0XFF,
        0XFF, 0XFF, 0X97, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X57, 0X57, 0X53, 0X72, 0XDB, 0XFF,
        0XFF, 0XFF, 0X97, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XDB, 0XDB, 0XB7, 0X72, 0X92, 0XDB,
        0XFF, 0XFF, 0X97, 0XFF, 0XF1, 0XEC, 0XEC, 0XF1, 0XF5, 0XF9, 0XFF, 0XDF, 0XDF, 0XBB, 0X6E, 0XDB,
        0XFF, 0XFF, 0X97, 0XFF, 0XF1, 0XA8, 0XEC, 0XF1, 0XF5, 0XFA, 0XF9, 0XF5, 0X97, 0XBB, 0X4D, 0XB7,
        0XFF, 0XFF, 0X97, 0XFF, 0XA4, 0X64, 0XA4, 0XC4, 0XC8, 0XE8, 0XE8, 0XC8, 0X93, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X97, 0XFF, 0XF1, 0X88, 0XAC, 0XF0, 0XF0, 0XF5, 0XF0, 0XF0, 0X97, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X97, 0XFF, 0XD5, 0XAD, 0X68, 0XD1, 0XF1, 0XF9, 0XF9, 0XD1, 0X97, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X93, 0XFF, 0XD2, 0XB1, 0X49, 0XB1, 0XD1, 0XFA, 0XF9, 0XD1, 0X77, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X73, 0XDF, 0XB2, 0X8E, 0X6E, 0XB2, 0XFA, 0XFE, 0XFD, 0XB2, 0X77, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X73, 0XDF, 0X93, 0X92, 0X92, 0X92, 0XB2, 0XD6, 0XF9, 0X92, 0X77, 0XBB, 0X4D, 0XB6,
        0XFF, 0XFF, 0X72, 0XDB, 0XDF, 0XBB, 0XBB, 0XBB, 0XBB, 0X9B, 0X9B, 0X9B, 0XBB, 0XB7, 0X4D, 0XB6,
        0XFF, 0XFF, 0X72, 0XDB, 0XDF, 0XDF, 0XDF, 0XDF, 0XBB, 0XBB, 0XBB, 0XBB, 0XBB, 0XB7, 0X4D, 0XB7,
        0XFF, 0XFF, 0X6E, 0X97, 0X97, 0X97, 0X97, 0X97, 0X93, 0X93, 0X93, 0X93, 0X92, 0X92, 0X6D, 0XB7,
        0XFF, 0XFF, 0XDB, 0X92, 0X6D, 0X4D, 0X4D, 0X4D, 0X4D, 0X4D, 0X4D, 0X4D, 0X4D, 0X6D, 0X92, 0XDB,
    },



};
//带ALPHA通道的图标.(文件夹图标)
const u8 pathico[2][1024] = {
    {
        //磁盘
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X80, 0X80, 0X80, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XFF, 0XFF, 0XFF, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0XFF, 0X00, 0X00, 0X00, 0XFF, 0X00, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00, 0XFF, 0XFF, 0XFF, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00, 0XC0, 0XC0, 0XC0, 0X00,
        0XC0, 0XC0, 0XC0, 0X00, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00, 0X80, 0X80, 0X80, 0X00,
        0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    },
    {
        //打开的文件夹
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00,
        0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00,
        0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00,
        0X02, 0X91, 0XDB, 0X00, 0X02, 0X91, 0XDB, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X90, 0XD9, 0X00, 0X93, 0XE5, 0XF9, 0X00,
        0X76, 0XD4, 0XF3, 0X00, 0X60, 0XC7, 0XEE, 0X00, 0X76, 0XD4, 0XF3, 0X00, 0X92, 0XE3, 0XF9, 0X00,
        0XAA, 0XF0, 0XFE, 0X00, 0XAD, 0XF2, 0XFF, 0X00, 0XAD, 0XF2, 0XFF, 0X00, 0XAD, 0XF2, 0XFF, 0X00,
        0XB0, 0XF5, 0XFF, 0X00, 0X02, 0X90, 0XD9, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X8E, 0XD6, 0X00, 0XAC, 0XF1, 0XFF, 0X00,
        0XAA, 0XEF, 0XFE, 0X00, 0XA8, 0XEF, 0XFD, 0X00, 0X8F, 0XE2, 0XF8, 0X00, 0X71, 0XD0, 0XF1, 0X00,
        0X57, 0XBF, 0XED, 0X00, 0XA5, 0XEA, 0XFD, 0X00, 0XA6, 0XEB, 0XFE, 0X00, 0XA6, 0XEB, 0XFE, 0X00,
        0XAB, 0XF0, 0XFF, 0X00, 0X02, 0X8E, 0XD6, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X8C, 0XD3, 0X00, 0XA8, 0XEE, 0XFD, 0X00,
        0XA3, 0XE9, 0XFC, 0X00, 0XA3, 0XE9, 0XFC, 0X00, 0XA4, 0XEA, 0XFD, 0X00, 0XAA, 0XF0, 0XFE, 0X00,
        0X4F, 0XB6, 0XE4, 0X00, 0X93, 0XD2, 0XE4, 0X00, 0X99, 0XDB, 0XED, 0X00, 0XA2, 0XE8, 0XFC, 0X00,
        0XA7, 0XED, 0XFD, 0X00, 0X02, 0X8C, 0XD3, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X8A, 0XD0, 0X00, 0XA5, 0XEB, 0XFC, 0X00,
        0XA0, 0XE6, 0XFB, 0X00, 0XA0, 0XE6, 0XFB, 0X00, 0XA0, 0XE6, 0XFB, 0X00, 0XA5, 0XEB, 0XFC, 0X00,
        0X44, 0XA9, 0XD7, 0X00, 0X8E, 0XCD, 0XE1, 0X00, 0X8E, 0XCD, 0XE1, 0X00, 0X9E, 0XE4, 0XFA, 0X00,
        0XA3, 0XE9, 0XFC, 0X00, 0X02, 0X8A, 0XD0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X88, 0XCC, 0X00, 0XA2, 0XE8, 0XFB, 0X00,
        0X9C, 0XE3, 0XF9, 0X00, 0X9C, 0XE3, 0XF9, 0X00, 0X9C, 0XE3, 0XF9, 0X00, 0XA2, 0XE8, 0XFB, 0X00,
        0X3D, 0X9F, 0XCD, 0X00, 0X89, 0XC9, 0XDE, 0X00, 0X89, 0XC9, 0XDE, 0X00, 0X99, 0XE0, 0XF7, 0X00,
        0X9F, 0XE5, 0XF9, 0X00, 0X02, 0X88, 0XCC, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X85, 0XC8, 0X00, 0X9D, 0XE5, 0XF9, 0X00,
        0X97, 0XDF, 0XF6, 0X00, 0X97, 0XDF, 0XF6, 0X00, 0X97, 0XDF, 0XF6, 0X00, 0X9D, 0XE5, 0XF9, 0X00,
        0X38, 0X9A, 0XC8, 0X00, 0X85, 0XC5, 0XDB, 0X00, 0X85, 0XC5, 0XDB, 0X00, 0X94, 0XDC, 0XF4, 0X00,
        0X9A, 0XE2, 0XF7, 0X00, 0X02, 0X85, 0XC8, 0X00, 0X02, 0X85, 0XC8, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X83, 0XC3, 0X00, 0X9A, 0XE1, 0XF7, 0X00,
        0X93, 0XDB, 0XF4, 0X00, 0X93, 0XDB, 0XF4, 0X00, 0X93, 0XDB, 0XF4, 0X00, 0X9A, 0XE1, 0XF7, 0X00,
        0X34, 0X95, 0XC2, 0X00, 0X80, 0XC0, 0XD9, 0X00, 0X80, 0XC0, 0XD9, 0X00, 0X8F, 0XD7, 0XF2, 0X00,
        0X96, 0XDD, 0XF6, 0X00, 0XFE, 0XFE, 0XFD, 0X00, 0X02, 0X83, 0XC3, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X80, 0XBF, 0X00, 0X96, 0XDE, 0XF6, 0X00,
        0X8F, 0XD8, 0XF2, 0X00, 0X8F, 0XD8, 0XF2, 0X00, 0X92, 0XDB, 0XF4, 0X00, 0X82, 0XCE, 0XEA, 0X00,
        0X31, 0X90, 0XBD, 0X00, 0X7B, 0XBD, 0XD7, 0X00, 0X7B, 0XBD, 0XD7, 0X00, 0X89, 0XD3, 0XEF, 0X00,
        0X90, 0XD9, 0XF3, 0X00, 0XF5, 0XF5, 0XEE, 0X00, 0X02, 0X80, 0XBF, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X7D, 0XBB, 0X00, 0X91, 0XDA, 0XF4, 0X00,
        0X8A, 0XD4, 0XF0, 0X00, 0X8A, 0XD4, 0XF0, 0X00, 0X91, 0XDA, 0XF4, 0X00, 0X2D, 0X8B, 0XB9, 0X00,
        0X65, 0XAE, 0XCE, 0X00, 0X77, 0XB9, 0XD4, 0X00, 0X7A, 0XBF, 0XDA, 0X00, 0X84, 0XCF, 0XEC, 0X00,
        0X8C, 0XD5, 0XF1, 0X00, 0XEB, 0XEB, 0XDD, 0X00, 0X02, 0X7D, 0XBB, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X7A, 0XB7, 0X00, 0X8D, 0XD6, 0XF2, 0X00,
        0X86, 0XD0, 0XED, 0X00, 0X86, 0XD0, 0XED, 0X00, 0X8D, 0XD6, 0XF2, 0X00, 0X2A, 0X87, 0XB4, 0X00,
        0X72, 0XB5, 0XD2, 0X00, 0X72, 0XB5, 0XD2, 0X00, 0X7F, 0XCB, 0XEA, 0X00, 0X7F, 0XCB, 0XEA, 0X00,
        0X87, 0XD1, 0XF0, 0X00, 0XFE, 0XC9, 0X40, 0X00, 0X02, 0X7A, 0XB7, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X76, 0XB0, 0X00, 0X89, 0XD3, 0XF0, 0X00,
        0X81, 0XCD, 0XEB, 0X00, 0X81, 0XCD, 0XEB, 0X00, 0X89, 0XD3, 0XF0, 0X00, 0X27, 0X83, 0XB0, 0X00,
        0X6E, 0XB3, 0XD0, 0X00, 0X6E, 0XB3, 0XD0, 0X00, 0X7B, 0XC8, 0XE8, 0X00, 0X7B, 0XC8, 0XE8, 0X00,
        0X84, 0XCF, 0XEE, 0X00, 0XF4, 0XB5, 0X2D, 0X00, 0X03, 0X76, 0XB0, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X6C, 0XA1, 0X00, 0X88, 0XD2, 0XF0, 0X00,
        0X7F, 0XCA, 0XE9, 0X00, 0X7E, 0XCA, 0XE9, 0X00, 0X86, 0XD0, 0XEF, 0X00, 0X27, 0X82, 0XAE, 0X00,
        0X74, 0XB6, 0XD5, 0X00, 0X74, 0XB6, 0XD5, 0X00, 0X81, 0XCB, 0XED, 0X00, 0X81, 0XCB, 0XED, 0X00,
        0X85, 0XCF, 0XF0, 0X00, 0X03, 0X6C, 0XA1, 0X00, 0X03, 0X46, 0X68, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X4A, 0X6E, 0X00, 0X38, 0X8D, 0XB7, 0X00,
        0X6E, 0XBB, 0XDF, 0X00, 0X84, 0XCE, 0XEE, 0X00, 0X85, 0XCF, 0XF0, 0X00, 0X03, 0X62, 0X92, 0X00,
        0X03, 0X55, 0X7E, 0X00, 0X03, 0X55, 0X7E, 0X00, 0X03, 0X62, 0X92, 0X00, 0X03, 0X62, 0X92, 0X00,
        0X03, 0X62, 0X92, 0X00, 0X03, 0X4A, 0X6E, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X6A, 0XA0, 0X00,
        0X03, 0X69, 0X9E, 0X00, 0X1E, 0X7E, 0XAE, 0X00, 0X53, 0XA6, 0XD0, 0X00, 0X03, 0X60, 0X8F, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X02, 0X29, 0X3D, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X03, 0X63, 0X94, 0X00, 0X03, 0X61, 0X92, 0X00, 0X03, 0X5E, 0X8D, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    },
};


#endif



























