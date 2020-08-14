#define PLUG_NAME "NELVirtualControlSurface"
#define PLUG_MFR "NeverEngineLabs"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "1.0.0"
#define PLUG_UNIQUE_ID 'rqJD'
#define PLUG_MFR_ID 'Acme'
#define PLUG_URL_STR "https://iplug2.github.io"
#define PLUG_EMAIL_STR "spam@me.com"
#define PLUG_COPYRIGHT_STR "Copyright 2019 Acme Inc"
#define PLUG_CLASS_NAME NELVirtualControlSurface

#define BUNDLE_NAME "NELVirtualControlSurface"
#define BUNDLE_MFR "NeverEngineLabs"
#define BUNDLE_DOMAIN "com"

#define PLUG_CHANNEL_IO "0-0"
#define SHARED_RESOURCES_SUBPATH "NELVirtualControlSurface"

#define PLUG_LATENCY 0
#define PLUG_TYPE 2
#define PLUG_DOES_MIDI_IN 1
#define PLUG_DOES_MIDI_OUT 1
#define PLUG_DOES_MPE 1
#define PLUG_DOES_STATE_CHUNKS 0
#define PLUG_HAS_UI 1
#define PLUG_WIDTH 650
#define PLUG_HEIGHT 400
#define PLUG_FPS 60
#define PLUG_SHARED_RESOURCES 0
#define PLUG_HOST_RESIZE 0

#define AUV2_ENTRY NELVirtualControlSurface_Entry
#define AUV2_ENTRY_STR "NELVirtualControlSurface_Entry"
#define AUV2_FACTORY NELVirtualControlSurface_Factory
#define AUV2_VIEW_CLASS NELVirtualControlSurface_View
#define AUV2_VIEW_CLASS_STR "NELVirtualControlSurface_View"

#define AAX_TYPE_IDS 'IPME'
#define AAX_TYPE_IDS_AUDIOSUITE 'IPMA'
#define AAX_PLUG_MFR_STR "Acme"
#define AAX_PLUG_NAME_STR "NELVirtualControlSurface\nIPEF"
#define AAX_PLUG_CATEGORY_STR "Effect"
#define AAX_DOES_AUDIOSUITE 0

#define VST3_SUBCATEGORY "Instrument|Synth"

#define APP_NUM_CHANNELS 2
#define APP_N_VECTOR_WAIT 0
#define APP_MULT 1
#define APP_COPY_AUV3 0
#define APP_SIGNAL_VECTOR_SIZE 64

#define ROBOTO_FN "Roboto-Regular.ttf"
#define MENLO_FN "Menlo-Regular.ttf"
#define FORK_AWESOME_FN "forkawesome-webfont.ttf"

#define PLANE_BG "deco_svg/gradient-plane-bg-text.svg"
#define LOGO_TEXT "deco_svg/logo_text.svg"

#define NBR_DUALDIALS 8
#define NBR_WIDGETS 3

#define WIDGET_OFF ICON_FK_SQUARE_O
#define WIDGET_ON ICON_FK_MINUS_SQUARE
#define WIDGET_OFF_NO_NET ICON_FK_CIRCLE_O
#define WIDGET_ON_NO_NET ICON_FK_MINUS_CIRCLE

#define DEFAULT_DIAL_ADDRESS "/dualDial/"

#define DEFAULT_TARGET_PORT  9090
#define DEFAULT_LISTENER_PORT  8080
