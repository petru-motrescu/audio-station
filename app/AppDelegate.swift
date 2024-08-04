import Cocoa

@main
class AppDelegate: NSObject, NSApplicationDelegate {
    
    let audioStation: AudioStationHandle
    let synth: SynthHandle
    
    override init() {
        self.audioStation = audio_station_init()
        self.synth = synth_init()
        audio_station_play(self.audioStation, self.synth)
    }
    
    func applicationDidFinishLaunching(_ aNotification: Notification) {
        
    }
    
    func applicationWillTerminate(_ aNotification: Notification) {
        audio_station_dispose(self.audioStation)
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        return true
    }
}
