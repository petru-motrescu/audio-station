import Foundation
import SceneKit

class Key : Equatable {
    var graphicsNode: SCNNode
    let audioSignalId: Int32
    let audioStation: AudioStationHandle
    
    init(_ audioStation: AudioStationHandle,
         _ audioSignalId: Int32,
         _ graphicsNode: SCNNode) {
        self.audioStation = audioStation
        self.audioSignalId = audioSignalId
        self.graphicsNode = graphicsNode
    }
    
    func press() {
        graphicsNode.position.z = -1.0
        audio_station_set_signal_live(self.audioStation, self.audioSignalId)
    }
    
    func release() {
        graphicsNode.position.z = 0.0
        audio_station_set_signal_silent(self.audioStation, self.audioSignalId)
    }
    
    static func == (lhs: Key, rhs: Key) -> Bool {
        return lhs.graphicsNode == rhs.graphicsNode
    }
}
