This example uses the archsites layer which is included in Geoserver by default.

Values from 'cat' field are used to build the isolines.

Apply the SLD style (_archsites.sld_) to the layer to see the values of each point.

To get more defined lines, you must change the RENDERER_TYPE parameter to sparse method:
  
    `RENDERER_TYPE: 1`