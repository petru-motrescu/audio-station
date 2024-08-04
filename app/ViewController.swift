import SceneKit
import QuartzCore

class ViewController: NSViewController {
    
    private var keys: [String: Key] = [:]
    private var pressedKey: Key? = nil
    private var synth: SynthHandle? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let scene = SCNScene(named: "art.scnassets/scene.scn")!
        
        let cameraNode = SCNNode()
        
        let camera = SCNCamera()
        camera.fieldOfView = 1
        camera.zFar = 2000
        
        cameraNode.camera = camera
        scene.rootNode.addChildNode(cameraNode)
        
        cameraNode.position = SCNVector3(x: 0, y: -360, z: 1000)
        cameraNode.eulerAngles = SCNVector3(x: 0.35, y: 0, z: 0)
        
        let lightNode = SCNNode()
        lightNode.light = SCNLight()
        lightNode.light!.type = .omni
        lightNode.position = SCNVector3(x: 0, y: 10, z: 10)
        scene.rootNode.addChildNode(lightNode)
        
        let ambientLightNode = SCNNode()
        ambientLightNode.light = SCNLight()
        ambientLightNode.light!.type = .ambient
        ambientLightNode.light!.color = NSColor.darkGray
        scene.rootNode.addChildNode(ambientLightNode)

        let scnView = self.view as! SCNView
        scnView.scene = scene
        scnView.allowsCameraControl = false
        scnView.showsStatistics = false
        scnView.backgroundColor = .black
        
        let gestureRecognizer = NSPressGestureRecognizer(target: self, action: #selector(handleGesture(_:)))
        gestureRecognizer.minimumPressDuration = 0
        var gestureRecognizers = scnView.gestureRecognizers
        gestureRecognizers.insert(gestureRecognizer, at: 0)
        scnView.gestureRecognizers = gestureRecognizers
        
        let appDelegate = NSApplication.shared.delegate as! AppDelegate
        self.synth = appDelegate.synth
        
        let keyNames = [
            "C1", "CD1", "D1", "DE1", "E1", "F1", "FG1", "G1", "GA1", "A1", "AB1", "B1",
            "C2", "CD2", "D2", "DE2", "E2", "F2", "FG2", "G2", "GA2", "A2", "AB2", "B2",
            "C3", "CD3", "D3", "DE3", "E3", "F3", "FG3", "G3", "GA3", "A3", "AB3", "B3",
        ]
        
        // TODO Better note identification
        var noteIndex: Int32 = 3
        for keyName in keyNames {
            let graphicsNode = findNode(scene, keyName)
            keys[keyName] = Key(keyName, self.synth!, noteIndex, graphicsNode)
            noteIndex += 1
        }
    }
    
    @objc
    func handleGesture(_ gestureRecognizer: NSGestureRecognizer) {
        let scnView = self.view as! SCNView
        let location = gestureRecognizer.location(in: scnView)
        let hitResults = scnView.hitTest(location, options: [:])
        if hitResults.count > 0 {
            let result = hitResults[0]
            if let key = keys[result.node.name!] {
                if (gestureRecognizer.state == .began || gestureRecognizer.state == .changed) {
                    pressKey(key)
                } else {
                    releaseKey(key)
                }
            }
        } else {
            releaseAllKeys()
        }
    }
    
    private func findNode(_ scene: SCNScene, _ name: String) -> SCNNode {
        return scene.rootNode.childNode(withName: name, recursively: true)!
    }
    
    private func pressKey(_ key: Key) {
        if (self.pressedKey != nil && self.pressedKey != key) {
            self.pressedKey?.release()
        }
        self.pressedKey = key
        key.press()
    }
    
    private func releaseKey(_ key: Key) {
        self.pressedKey = nil
        key.release()
    }
    
    private func releaseAllKeys() {
        if (self.pressedKey != nil) {
            releaseKey(self.pressedKey!)
        }
    }
}
