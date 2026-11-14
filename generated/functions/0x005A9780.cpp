// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9780 rf_ui_initialize_default_theme_once
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Guard DWORD0x1CF7C10;already initialized does nothing and return is incidental. First call clears tooltip-ready BYTE0x1CF75C6,sets deadline0x1CF7644 offset0,copies sentinel0x1CF7678 into window heads0x1CF7B5C/60,registers no-op0x5A9710 with atexit,sets8 feedback sound IDs0x1CF75A0..BC=-1,clears0x1CF75DC. Explicitly writes79 default RGBA colors through color setter,then guard=1;returns last color pointer. Unlike no-op palette constructors,this supplies actual byte values. Exact address=(R,G,B,A) table from79 matched call sites: 0x1CF7608=(0,0,0,96) 0x1CF760C=(255,255,255,255) 0x1CF7610=(0,0,0,0) 0x1CF7C08=(144,144,144,255) 0x1CF7C0C=(0,0,0,255) 0x1CF7C00=(128,128,128,196) 0x1CF7C04=(48,48,48,196) 0x1CF7600=(96,92,88,224) 0x1CF75F8=(128,128,128,224) 0x1CF7604=(96,92,88,224) 0x1CF75FC=(48,48,48,224) 0x1CF7B6C=(0,0,0,0)
// 0x1CF7B64=(128,128,128,196) 0x1CF7B68=(32,32,32,196) 0x1CF7B70=(144,144,144,255) 0x1CF7B74=(0,0,0,255) 0x1CF7B80=(255,255,0,24) 0x1CF7B78=(128,128,128,196) 0x1CF7B7C=(32,32,32,196) 0x1CF7B84=(160,160,160,255) 0x1CF7B88=(0,0,0,255) 0x1CF7B94=(0,0,0,0) 0x1CF7B8C=(128,128,128,196) 0x1CF7B90=(48,48,48,196) 0x1CF7B98=(48,48,48,255) 0x1CF7B9C=(112,112,112,255) 0x1CF762C=(0,0,0,0) 0x1CF7630=(144,144,144,255) 0x1CF7634=(0,0,0,255) 0x1CF7638=(0,0,0,0) 0x1CF763C=(48,48,48,255) 0x1CF7640=(112,112,112,255) 0x1CF7BA0=(255,255,255,255) 0x1CF7BA4=(255,0,0,255) 0x1CF7BA8=(144,144,144,255) 0x1CF7BAC=(0,0,0,255) 0x1CF7BB0=(255,255,255,255) 0x1CF7BB4=(255,0,0,255) 0x1CF7BB8=(196,196,196,255) 0x1CF7BBC=(0,0,0,255) 0x1CF7BC0=(128,128,128,255) 0x1CF7BC4=(255,0,0,255) 0x1CF7BC8=(196,196,196,255) 0x1CF7BCC=(0,0,0,255) 0x1CF7BD0=(172,172,172,255) 0x1CF7BD4=(255,0,0,255) 0x1CF7BD8=(48,48,48,255)
// 0x1CF7BDC=(112,112,112,255) 0x1CF7650=(48,48,48,224) 0x1CF7648=(128,128,128,128) 0x1CF764C=(24,24,24,196) 0x1CF7654=(188,188,188,255) 0x1CF7658=(0,0,0,255) 0x1CF765C=(255,140,0,160) 0x1CF7668=(0,0,0,0) 0x1CF7660=(128,128,128,128) 0x1CF7664=(24,24,24,196) 0x1CF766C=(144,144,144,255) 0x1CF7670=(24,24,24,255) 0x1CF7674=(0,0,0,0) 0x1CF75EC=(62,66,94,255) 0x1CF75E4=(86,92,125,255) 0x1CF75E8=(22,25,50,255) 0x1CF75F0=(120,120,120,255) 0x1CF75F4=(128,128,128,255) 0x1CF7614=(170,170,170,255) 0x1CF7618=(0,0,0,255) 0x1CF761C=(170,170,0,255) 0x1CF7620=(0,0,0,255) 0x1CF7624=(140,140,0,255) 0x1CF7628=(0,0,0,255) 0x1CF7BE8=(48,48,48,224) 0x1CF7BE0=(128,128,128,128) 0x1CF7BE4=(24,24,24,196) 0x1CF7BF4=(0,0,0,0) 0x1CF7BEC=(128,128,128,128) 0x1CF7BF0=(24,24,24,196) 0x1CF7BF8=(144,144,144,255) 0x1CF7BFC=(24,24,24,255)
_BYTE *rf_ui_initialize_default_theme_once()
{
  _BYTE *result; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( !unk_1CF7C10 )
  {
    unk_1CF75C6 = 0;
    rf_clock_deadline_set_wrapped_offset(&unk_1CF7644, 0);
    unk_1CF7B5C = dword_1CF7678;
    unk_1CF7B60 = dword_1CF7678;
    atexit(rf_ui_noop_callback);
    for ( i = 0; i < 8; ++i )
      dword_1CF75A0[i] = -1;
    unk_1CF75DC = 0;
    rf_color4_set_bytes_return_destination(byte_1CF7608, 0, 0, 0, 96);
    rf_color4_set_bytes_return_destination(byte_1CF760C, 255, 255, 255, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7610, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7C08, 144, 144, 144, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7C0C, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7C00, 128, 128, 128, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7C04, 48, 48, 48, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7600, 96, 92, 88, 224);
    rf_color4_set_bytes_return_destination(byte_1CF75F8, 128, 128, 128, 224);
    rf_color4_set_bytes_return_destination(byte_1CF7604, 96, 92, 88, 224);
    rf_color4_set_bytes_return_destination(byte_1CF75FC, 48, 48, 48, 224);
    rf_color4_set_bytes_return_destination(byte_1CF7B6C, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7B64, 128, 128, 128, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B68, 32, 32, 32, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B70, 144, 144, 144, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7B74, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7B80, 255, 255, 0, 24);
    rf_color4_set_bytes_return_destination(byte_1CF7B78, 128, 128, 128, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B7C, 32, 32, 32, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B84, 160, 160, 160, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7B88, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7B94, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7B8C, 128, 128, 128, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B90, 48, 48, 48, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7B98, 48, 48, 48, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7B9C, 112, 112, 112, 255);
    rf_color4_set_bytes_return_destination(byte_1CF762C, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7630, 144, 144, 144, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7634, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7638, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF763C, 48, 48, 48, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7640, 112, 112, 112, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BA0, 255, 255, 255, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BA4, 255, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BA8, 144, 144, 144, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BAC, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BB0, 255, 255, 255, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BB4, 255, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BB8, 196, 196, 196, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BBC, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BC0, 128, 128, 128, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BC4, 255, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BC8, 196, 196, 196, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BCC, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BD0, 172, 172, 172, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BD4, 255, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BD8, 48, 48, 48, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BDC, 112, 112, 112, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7650, 48, 48, 48, 224);
    rf_color4_set_bytes_return_destination(byte_1CF7648, 128, 128, 128, 128);
    rf_color4_set_bytes_return_destination(byte_1CF764C, 24, 24, 24, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7654, 188, 188, 188, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7658, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF765C, 255, 140, 0, 160);
    rf_color4_set_bytes_return_destination(byte_1CF7668, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7660, 128, 128, 128, 128);
    rf_color4_set_bytes_return_destination(byte_1CF7664, 24, 24, 24, 196);
    rf_color4_set_bytes_return_destination(byte_1CF766C, 144, 144, 144, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7670, 24, 24, 24, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7674, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF75EC, 62, 66, 94, 255);
    rf_color4_set_bytes_return_destination(byte_1CF75E4, 86, 92, 125, 255);
    rf_color4_set_bytes_return_destination(byte_1CF75E8, 22, 25, 50, 255);
    rf_color4_set_bytes_return_destination(byte_1CF75F0, 120, 120, 120, 255);
    rf_color4_set_bytes_return_destination(byte_1CF75F4, 128, 128, 128, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7614, 170, 170, 170, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7618, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF761C, 170, 170, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7620, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7624, 140, 140, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7628, 0, 0, 0, 255);
    rf_color4_set_bytes_return_destination(byte_1CF7BE8, 48, 48, 48, 224);
    rf_color4_set_bytes_return_destination(byte_1CF7BE0, 128, 128, 128, 128);
    rf_color4_set_bytes_return_destination(byte_1CF7BE4, 24, 24, 24, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7BF4, 0, 0, 0, 0);
    rf_color4_set_bytes_return_destination(byte_1CF7BEC, 128, 128, 128, 128);
    rf_color4_set_bytes_return_destination(byte_1CF7BF0, 24, 24, 24, 196);
    rf_color4_set_bytes_return_destination(byte_1CF7BF8, 144, 144, 144, 255);
    result = rf_color4_set_bytes_return_destination(byte_1CF7BFC, 24, 24, 24, 255);
    unk_1CF7C10 = 1;
  }
  return result;
}

