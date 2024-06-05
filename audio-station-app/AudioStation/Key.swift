import Foundation
import SceneKit

class Key : Equatable {
    let name: String
    var graphicsNode: SCNNode
    let noteIndex: Int32
    let synth: SynthHandle
    let isBlack: Bool
    var isPressed: Bool
    
    init(_ name: String,
         _ synth: SynthHandle,
         _ noteIndex: Int32,
         _ graphicsNode: SCNNode
    ) {
        self.name = name
        self.synth = synth
        self.noteIndex = noteIndex
        self.graphicsNode = graphicsNode
        self.isBlack = name.count > 2
        self.isPressed = false
    }
    
    func press() {
        if (!self.isPressed) {
            self.isPressed = true
            graphicsNode.position.z = pressedZ()
            synth_play_note(self.synth, self.noteIndex)
        }
    }
    
    func release() {
        if (self.isPressed) {
            self.isPressed = false
            graphicsNode.position.z = defaultZ()
            synth_stop_note(self.synth, self.noteIndex)
        }
    }
    
    static func == (lhs: Key, rhs: Key) -> Bool {
        return lhs.graphicsNode == rhs.graphicsNode
    }
    
    private func pressedZ() -> Double {
        if self.isBlack {
            return 0.5
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
