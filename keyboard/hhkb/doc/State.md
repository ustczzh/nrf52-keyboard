# 状态图

## BLE

## USB

```plantuml
@startuml
left to right direction
state "usb" as usb {
  usb.unattached --> usb.connected
  usb.connected --> usb.suspended
  usb.suspended --> usb.unattached

  state "idle" as usb.idle {
    usb.idle --> usb.downloading : 
  }

  state "downloading" as usb.downloading {
    usb.downloading : do/streamChunk
    usb.downloading --> usb.paused : PAUSE
    usb.downloading --> usb.finished : DONE
  }

  state "paused" as usb.paused {
    usb.paused --> usb.downloading : RESUME
    usb.paused --> usb.finished : CANCEL
  }

  state "finished" as usb.finished {
    usb.finished : onEntry/cleanCache
  }
}
@enduml
```
