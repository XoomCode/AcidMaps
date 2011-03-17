package com.xoomcode.acidmaps
{
	import com.xoomcode.acidmaps.interpolate.InterpolationStrategy;
	import com.xoomcode.acidmaps.renderer.RendererType;
	import com.xoomcode.acidmaps.simplify.SimplifyMethod;
	
	import org.openscales.core.layer.params.ogc.WMSParams;
	
	public class AMSParameters extends WMSParams
	{
		
		private var _valueColumn:String;
		
		private var _filter:String;
		
		private var _simplifyMethod:int = SimplifyMethod.COPY;
		
		private var _simplifySize:int = 64;
		
		private var _intervals:Array = new Array();
		
		private var _intervalsColors:Array = new Array();
		
		private var _rendererType:int = RendererType.SPARSE;
		
		private var _interpolationStrategy:int = InterpolationStrategy.LINEAR;
		
		private var _interpolationParameter:int = 32;
		
		public function AMSParameters(layers:String, valueColumn:String) {
			super(layers);
			service = "AMS";
			this.valueColumn = valueColumn;
		}
		
		public function set filter(value:String):void {
			_filter = value;
		}
		
		public function get filter():String {
			return _filter;
		}
		
		public function set valueColumn(value:String):void {
			_valueColumn = value;
		}
		
		public function get valueColumn():String {
			return _valueColumn;
		}
		
		public function set simplifyMethod(value:int):void {
			_simplifyMethod = value;
		}
		
		public function get simplifyMethod():int {
			return _simplifyMethod;
		}
		
		public function set simplifySize(value:int):void {
			_simplifySize = value;
		}
		
		public function get simplifySize():int {
			return _simplifySize;
		}
		
		public function set intervals(value:Array):void {
			_intervals = value;
		}
		
		public function get intervals():Array {
			return _intervals;
		}
		
		public function set intervalsColors(value:Array):void {
			_intervalsColors = value;
		}
		
		public function get intervalsColors():Array {
			return _intervalsColors;
		}
		
		public function set rendererType(value:int):void {
			_rendererType = value;
		}
		
		public function get rendererType():int {
			return _rendererType;
		}
		
		public function set interpolationStrategy(value:int):void {
			_interpolationStrategy = value;
		}
		
		public function get interpolationStrategy():int {
			return _interpolationStrategy;
		}
		
		public function set interpolationParameter(value:int):void {
			_interpolationParameter = value;
		}
		
		public function get interpolationParameter():int {
			return _interpolationParameter;
		}
		
		override public function toGETString():String {
			var str:String = super.toGETString();
			
			if (_filter != null){
				str +="&CQL_FILTER=(" + _filter + ")";
			}
			
			if (_valueColumn != null){
				str +="&VALUE_COLUMN=" + _valueColumn;
			}
			
			str += "&SIMPLIFY_METHOD=" + _simplifyMethod;
			
			str += "&SIMPLIFY_SIZE=" + _simplifySize;
			
			if(intervals != null && intervals.length > 0){
				str += "&INTERVALS[]=" + buildIntervalsString();
			}
			
			if(intervalsColors != null && intervalsColors.length > 0){
				str += "&INTERVALS_COLORS[]=" + buildIntervalsColorsString();
			}
			
			str += "&RENDERER_TYPE=" + _rendererType;
			
			str += "&INTERPOLATION_STRATEGY=" + _interpolationStrategy;
			
			str += "&INTERPOLATION_PARAMETER=" + _interpolationParameter;
			
			return str;	
		}
		
		private function buildIntervalsColorsString():String {
			var hexaIntervalsColors:Array = new Array();
			for each(var value:uint in intervalsColors){
				hexaIntervalsColors.push("0x" + value.toString(16));
			}
			return buildArrayString(hexaIntervalsColors);
		}
		
		private function buildIntervalsString():String {
			return buildArrayString(intervals);
		}
		
		private function buildArrayString(arr:Array):String {
			var arrayStr:String = "";
			
			for each(var value:Object in arr){
				if(arrayStr == ""){
					arrayStr += value;
				} else {
					arrayStr += "," + value;
				}
			}
			
			return arrayStr;
		}

	}
}