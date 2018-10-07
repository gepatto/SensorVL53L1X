
package sensors.vl53l1x.events;

import openfl.events.Event;

class DistanceEvent extends Event {
    
    public static inline var DISTANCE = "sensor_event_distance";
    public var distance(default, null) : Int;

    public function new( type:String,  distance:Int)
    {
        super(type, true, true);
        this.distance = distance;
    }

    public override function clone() : Event
    {
		return new DistanceEvent( type, this.distance );
	}

	public override function toString() : String
    {
       return 'DistanceEvent type=$type distance=${this.distance}';
	}
}