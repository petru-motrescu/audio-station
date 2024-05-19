import Cocoa

@main
class AppDelegate: NSObject, NSApplicationDelegate {
    
    let audioStation: AudioStationHandle
    let synth: SynthHandle
    let track: TrackHandle
    
    override init() {
        self.audioStation = audio_station_init()
        self.synth = synth_init()
        self.track = track_init()
        track_add_synth(self.track, self.synth)
        audio_station_play(self.audioStation, self.track)
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
