import SceneKit
import QuartzCore

class ViewController: NSViewController {
    
    private var keys: [String: Key] = [:]
    private var pressedKey: Key? = nil
    private var audioStation: AudioStationHandle? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let scene = SCNScene(named: "art.scnassets/scene.scn")!
        
        let cameraNode = SCNNode()
        
        let camera = SCNCamera()
        camera.fieldOfView = 10
        camera.zFar = 110
        
        cameraNode.camera = camera
        scene.rootNode.addChildNode(cameraNode)
        
        cameraNode.position = SCNVector3(x: 0, y: 0, z: 100)
        
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
        
        for octave in 1...2 {
            for index in 1...7 {
                let keyName = "O\(octave)-K\(index)"
                keys[keyName] = Key(findNode(scene, keyName))
            }
        }
        
        let appDelegate = NSApplication.shared.delegate as! AppDelegate
        self.audioStation = appDelegate.audioStation
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
        audio_station_play(self.audioStation!)
    }
    
    private func releaseKey(_ key: Key) {
        self.pressedKey = nil
        key.release()
        audio_station_stop(self.audioStation!)
    }
    
    private func releaseAllKeys() {
        if (self.pressedKey != nil) {
            self.pressedKey?.release()
        }
    }
}
