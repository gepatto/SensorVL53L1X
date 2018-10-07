package sensors;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

import openfl.events.Event;
import openfl.events.EventDispatcher;
import lime.system.BackgroundWorker;
import lime.app.Future;
import sensors.vl53l1x.events.DistanceEvent;
import sensors.vl53l1x.events.SensorEvent;

class SensorVL53L1X extends EventDispatcher{
 	
    private static var sensorInitialize  = Lib.load ("SensorVL53L1X", "sensorvl53xl1_initialize", 0);
    private static var sensorGetDistance = Lib.load ("SensorVL53L1X", "sensorvl53xl1_getDistance", 0);

    private var worker:BackgroundWorker;
    private var continueMeasuring:Bool = false;

	public function new():Void{
        super();
	}
    
    public function initialize():Bool{
        return sensorInitialize();
    }

    public function getDistance():Void{
        var f = new Future( function(){
            var d = sensorGetDistance();
            dispatchEvent( new DistanceEvent(DistanceEvent.DISTANCE, d )) ;
        });
    }

    public function startMeasuring():Void{
        if(worker!=null) return;
        continueMeasuring = true;
        worker = new BackgroundWorker();
        worker.doWork.add( function( val) {
            while( continueMeasuring ){
                var d = sensorGetDistance();
                dispatchEvent( new DistanceEvent(DistanceEvent.DISTANCE, d )) ;
            }
            worker.sendComplete(true);
        });
        
        worker.onComplete.add( function( result) {
            worker = null;
        });

        worker.onError.add( function( error) {
            dispatchEvent( new SensorEvent(SensorEvent.ERROR, "Error in measuring BackgroundWorker"));
        });

        worker.run(0);
    }

    public function stopMeasuring():Void{
        continueMeasuring = false;
    }

}