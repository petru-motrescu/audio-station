import Cocoa

@main
class AppDelegate: NSObject, NSApplicationDelegate {
    
    let audioStation: AudioStationHandle = audio_station_init()
    
    func applicationDidFinishLaunching(_ aNotification: Notification) {
        
    }
    
    func applicationWillTerminate(_ aNotification: Notification) {
        audio_station_dispose(self.audioStation)
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        return true
    }
}
