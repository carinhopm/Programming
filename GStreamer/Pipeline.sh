gst-launch-1.0 videomixer name=mix ! ximagesink \
multifilesrc location="image.jpg" caps="image/jpeg,framerate=1/1" ! jpegdec ! videoconvert ! videorate ! mix. \
filesrc location="audio.mp3" ! decodebin ! tee name="decoder" decoder. ! queue ! audioconvert ! alsasink \
decoder. ! queue ! audioconvert ! goom ! textoverlay font-desc="Sans Bold 30" text='GOOM' color=4294967040 ! mix.