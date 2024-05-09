import Foundation
import SceneKit

class Key : Equatable {
    let name: String
    var graphicsNode: SCNNode
    let audioSignalId: Int32
    let audioStation: AudioStationHandle
    let isBlack: Bool
    
    init(_ name: String,
         _ audioStation: AudioStationHandle,
         _ audioSignalId: Int32,
         _ graphicsNode: SCNNode
    ) {
        self.name = name
        self.audioStation = audioStation
        self.audioSignalId = audioSignalId
        self.graphicsNode = graphicsNode
        self.isBlack = name.count > 2
    }
    
    func press() {
        graphicsNode.position.z = pressedZ()
        audio_station_set_signal_live(self.audioStation, self.audioSignalId)
    }
    
    func release() {
        graphicsNode.position.z = defaultZ()
        audio_station_set_signal_silent(self.audioStation, self.audioSignalId)
    }
    
    static func == (lhs: Key, rhs: Key) -> Bool {
        return lhs.graphicsNode == rhs.graphicsNode
    }
    
    private func pressedZ() -> Double {
        print(self.isBlack)
        if self.isBlack {
            return 0.0
        } else {
            return -1.0
        }
    }
    
    private func defaultZ() -> Double {
        if self.isBlack {
            return 1.0
        } else {
            return 0.0
        }
    }
}
