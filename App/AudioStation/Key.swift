import Foundation
import SceneKit

class Key : Equatable {
    var node: SCNNode
    
    init(_ node: SCNNode) {
        self.node = node
    }
    
    func press() {
        node.position.z = -1.0
    }
    
    func release() {
        node.position.z = 0.0
    }
    
    static func == (lhs: Key, rhs: Key) -> Bool {
        return lhs.node == rhs.node
    }
}
