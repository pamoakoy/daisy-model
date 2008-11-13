using System;
using System.Collections;
using global::OpenMI.Standard;
using Oatc.OpenMI.Sdk.Backbone;
using Oatc.OpenMI.Sdk.Wrapper;

namespace dk.ku.life.Daisy.OpenMI
{
    public class DaisyWrapper : Oatc.OpenMI.Sdk.Wrapper.IEngine
    {
        
        /* Declarations. */
        private Daisy _daisyEngine;
        private string description;
        private uint columns;
        private DateTime start_time;
        private DateTime end_time;

        public uint ScopeSize() { return _daisyEngine.ScopeSize(); }
        public Scope GetScope(int index) { return _daisyEngine.GetScope(index); }
        public DateTime GetTime() { return _daisyEngine.GetTime(); }
        public DateTime GetEndTime() { return end_time; }
        public DateTime StartTime { get { return start_time; } }
        public DateTime EndTime { get { return end_time; } }
        public string GetDescription() { return description; }

        /* Test of Daisy daisy */
        public uint CountColumns() { return _daisyEngine.CountColumns(); }
        public bool IsRunning() { return _daisyEngine.IsRunning(); }

        /* Initialisatio */
        public void InitializeDaisy(string filename)
        {
            /* Link and initialize the daisy subsystem. */
            _daisyEngine = new Daisy();
            _daisyEngine.ParseFile(filename);
            _daisyEngine.Initialize();

            ///* Initialize attribute list. */
            AList alist = _daisyEngine.ProgramAList();

            if (!alist.Check("description"))
                description = "No description";
            description = alist.GetString("description");

            ///* Start time */
            start_time = _daisyEngine.GetTime();

            ///* End time.*/
            AList stop = alist.GetAList("stop");
            int hour = stop.GetInteger("hour");
            int year = stop.GetInteger("year");
            int month = stop.GetInteger("month");
            int mday = stop.GetInteger("mday");
            end_time = new DateTime(year, month, mday, hour, 0, 0);

            columns = _daisyEngine.CountColumns();

            Console.WriteLine("Starting simulation.");
            _daisyEngine.Start();
        }  
        // Input and output exchange items (part of Oatc.OpenMI.Sdk.Backbone.InputExchangeItem and 
        // Oatc.OpenMI.Sdk.Backbone.OutputExchangeItem:
        ArrayList _inputExchangeItems;
        ArrayList _outputExchangeItems;
        Hashtable _elementSets;
        string FilePath;
        string ModelDescription;

        struct DimTab
        {
            public string dimension;
            public string description;

            public int length;
            public int mass;
            public int time;
            public int temperature;
            public int AmountOfSubstance;
            public double factor;
            public double offset;

            public DimTab(string dim, string desc, int l, int m, int ti, int temp,
                          int amount, double f, double off)
            {
                dimension = dim;
                description = desc;
                length = l;
                mass = m;
                time = ti;
                temperature = temp;
                AmountOfSubstance = amount;//mol
                factor = f;
                offset = off;
            }
        }
        static DimTab[] dimtab = 
    {
        new DimTab ("none", "unitless", 0, 0, 0, 0, 0, 1e0, 0),
        new DimTab ("m^2/m^2", "unitless", 0, 0, 0, 0, 0, 1e0, 0),
        new DimTab ("m^3/m^3", "unitless", 0, 0, 0, 0, 0, 1e0, 0),
        new DimTab ("m/m", "unitless", 0, 0, 0, 0, 0, 1e0, 0),
        new DimTab ("h", "hour", 0, 0, 1, 0, 0, 60*60, 0),
        new DimTab ("ha", "hectar", 2, 0, 0, 0, 0, 1e4, 0),
        new DimTab ("km", "kilometer", 1, 0, 0, 0, 0, 1e3, 0),
        new DimTab ("m", "meter", 1, 0, 0, 0, 0, 1e0, 0),
        new DimTab ("cm", "centimeter", 1, 0, 0, 0, 0, 1e-2, 0),
        new DimTab ("mm", "millimeter", 1, 0, 0, 0, 0, 1e-3, 0),
        new DimTab ("kg", "kilogram", 0, 1, 0, 0, 0, 1e0, 0),
        new DimTab ("g", "gram", 0, 1, 0, 0, 0, 1e-3, 0),
        new DimTab ("mg", "milligram", 0, 1, 0, 0, 0, 1e-6, 0),
        new DimTab ("kg/ha", "kilo per hectar", -2, 1, 0, 0, 0, 1e-4, 0),
        new DimTab ("kg N/ha", "kilo N per hectar", -2, 1, 0, 0, 0, 1e-4, 0),
        new DimTab ("kg C/ha", "kilo C per hectar", -2, 1, 0, 0, 0, 1e-4, 0),
        new DimTab ("kg N/ha/h", "kilo N per hectar per hour", -2, 1, -1, 0, 0, 1e-4/(60*60), 0),
        new DimTab ("cm/h", "centimeter per hour", 1, 0, -1, 0, 0, 1e-2/(60*60), 0),
        new DimTab ("mm/s", "millimeter per second", 1, 0, -1, 0, 0, 1e-3, 0),
        new DimTab ("mm/h", "millimeter per hour", 1, 0, -1, 0, 0, 1e-3/(60*60), 0),
        new DimTab ("mm/d", "millimeter per day", 1, 0, -1, 0, 0, 1e-3/(24*60*60), 0),
        new DimTab ("Mg DM/ha", "megagram DM per hectar", -2, 1, 0, 0, 0, 1e3*1e-4, 0),
        new DimTab ("g/cm^3", "gram per cubic centimeter", -3, 1, 0, 0, 0, 1e-3*1e6, 0),
        new DimTab ("g/cm^2/h", "gram per square centimeter", -2, 1, -1, 0, 0, 1e-3*1e4/(60*60), 0),
        new DimTab ("dg C", "degree Celcius", 0, 0, 0, 1, 0, 1, 273.15)
    };
        public Quantity Quantity(string dimension, string description, string name)
        {
            for (int i = 0; i < dimtab.Length; i++)
            {
                if (dimtab[i].dimension != dimension)
                    continue;
                Dimension unit_dimension = new Dimension();
                unit_dimension.SetPower(DimensionBase.Length, dimtab[i].length);
                unit_dimension.SetPower(DimensionBase.Mass, dimtab[i].mass);
                unit_dimension.SetPower(DimensionBase.Time, dimtab[i].time);
                unit_dimension.SetPower(DimensionBase.Temperature, dimtab[i].temperature);
                unit_dimension.SetPower(DimensionBase.AmountOfSubstance, dimtab[i].AmountOfSubstance);

                double factor = dimtab[i].factor;
                double offset = dimtab[i].offset;
                string dimDescription = dimtab[i].description;
                Unit unit = new Unit(dimension, factor, offset, dimDescription);
                return new Quantity(unit, description, name, global::OpenMI.Standard.ValueType.Scalar, unit_dimension);
            }
            return new Quantity(new Unit(dimension, 1.0, 0, "Unrecognized dimension"), description, name, global::OpenMI.Standard.ValueType.Scalar, new Dimension());
        }
        public void Initialize(Hashtable properties) //part of System.Collections
        {
            _inputExchangeItems = new ArrayList();
            _outputExchangeItems = new ArrayList();
            _elementSets = new Hashtable();
            FilePath = ((string)properties["FilePath"]);

            InitializeDaisy((string)properties["FilePath"]);
            ModelDescription = ((string)GetDescription());

            for (int i = 0; i < _daisyEngine.ScopeSize(); i++)
            {
                Scope scope = _daisyEngine.GetScope(i);

                // Attribut column?
                if (!scope.HasString("column"))
                    continue;

                // Create element.
                string columnID = scope.String("column");
                Element element = new Element (columnID);
                if (_daisyEngine.HasColumn(columnID))
                {
                    Column column = _daisyEngine.GetColumn(columnID);
                    for (uint ii = 0; ii < column.LocationSize(); ii++)
                    {
                        double x = column.LocationX(ii);
                        double y = column.LocationY(ii);
                        double z = 0.0;
                        element.AddVertex(new Vertex(x, y, z));
                    }
                }                          

                // Add exchange items.
                for (uint j = 0; j < scope.NumberSize(); j++)
                {
                    string name = scope.NumberName(j);
                    ElementSet elementSet;

                    // Find or create element set.
                    if (_elementSets.Contains(name))
                    {
                        elementSet = (ElementSet)_elementSets[name];
                        elementSet.Description += " " + columnID;
                        // TODO: We should test the type matches here.                    
                    }
                    else
                    {
                        switch (element.VertexCount)
                        {
                            case 0:
                                // ID based
                                elementSet = new ElementSet(columnID, name, ElementType.XYPoint, new SpatialReference(""));
                                break;
                            case 1:
                                // Point based
                                elementSet = new ElementSet(columnID, name, ElementType.XYPoint, new SpatialReference(""));
                                break;
                            case 2:
                                // Error
                                throw new ApplicationException("Error: Column must not contain exactly two (X Y)-points!");
                            default:
                                // Polygon
                                elementSet = new ElementSet(columnID, name, ElementType.XYPolygon, new SpatialReference(""));
                                break;
                        }
                        _elementSets[name] = elementSet;
                        string dim = scope.Dimension(name);
                        string description = scope.Description(name);

                        Quantity quantity = Quantity(dim, description, name);
                        if (scope.Writeable())
                        {
                            InputExchangeItem input = new InputExchangeItem();
                            input.Quantity = quantity;
                            input.ElementSet = elementSet;
                            _inputExchangeItems.Add(input);
                        }
                        else
                        {
                            OutputExchangeItem output = new OutputExchangeItem();
                            output.Quantity = quantity;
                            output.ElementSet = elementSet;
                            _outputExchangeItems.Add(output);
                        }
                    }

                    // Add it.
                    elementSet.AddElement(element);
                }
            }
        }
        public string GetModelID()
        {
            // ID for data (filnavn)
            return FilePath;
        }
        public string GetModelDescription()
        {
            return ModelDescription;
        }
        public string GetComponentID()
        {
            return "Daisy";
        }
        public string GetComponentDescription()
        {
            return "Daisy version " + DLL.daisy_version();
        }
        public global::OpenMI.Standard.ITime GetCurrentTime()
        {
            Oatc.OpenMI.Sdk.Backbone.TimeStamp current_time = new TimeStamp();
            current_time.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(_daisyEngine.GetTime());
            return (global::OpenMI.Standard.ITime)(current_time);
        }
        public global::OpenMI.Standard.ITime GetInputTime(string QuantityID, string ElementSetID)
        {
            // TID MAN �NSKER INPUT TIL (FORSKUDT TIDSKRIDT)
            Oatc.OpenMI.Sdk.Backbone.TimeStamp current_time = new TimeStamp();
            current_time.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(_daisyEngine.GetTime());
            return (global::OpenMI.Standard.ITime)(current_time);
        }
        public global::OpenMI.Standard.ITimeSpan GetTimeHorizon()
        {
            DateTime daisy_start_time = StartTime;
            DateTime daisy_end_time = EndTime;

            Oatc.OpenMI.Sdk.Backbone.TimeStamp start = new Oatc.OpenMI.Sdk.Backbone.TimeStamp();
            start.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(daisy_start_time);

            Oatc.OpenMI.Sdk.Backbone.TimeStamp end = new Oatc.OpenMI.Sdk.Backbone.TimeStamp();
            end.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(daisy_end_time);

            return (global::OpenMI.Standard.ITimeSpan)(new Oatc.OpenMI.Sdk.Backbone.TimeSpan(start, end));
        }
        public global::OpenMI.Standard.ITimeStamp GetEarliestNeededTime()
        {
            return (global::OpenMI.Standard.ITimeStamp)this.GetCurrentTime();
        }
        public global::OpenMI.Standard.IValueSet GetValues(string QuantityID, string ElementSetID)
        {
            double[] returnValues = new double[1];
            bool found = false;

            for (int i = 0; i < _daisyEngine.ScopeSize(); i++)
            {
                Scope scope = _daisyEngine.GetScope(i);

                if (!scope.HasString("column"))
                    continue;
                if (scope.Writeable())
                    continue;

                if (scope.String("column") != ElementSetID)
                    continue;

                for (uint j = 0; j < scope.NumberSize(); j++)
                {
                    if (scope.NumberName(j) == QuantityID)
                    {
                        if (found)
                            throw new Exception("Duplicate QuantityID: '" + QuantityID + "' in DaisyEngine");
                        if (scope.HasNumber(QuantityID))
                            returnValues[0] = scope.Number(QuantityID);
                        else
                            returnValues[0] = GetMissingValueDefinition();
                        found = true;
                    }
                }
            }
            if (!found)
                throw new Exception("No QuantityID: '" + QuantityID + "' defined in DaisyEngine");

            Oatc.OpenMI.Sdk.Backbone.ScalarSet values = new Oatc.OpenMI.Sdk.Backbone.ScalarSet(returnValues);
            return values;
        }
        public double GetMissingValueDefinition()
        {
            return -999999.99;
        }
        public Oatc.OpenMI.Sdk.Backbone.InputExchangeItem GetInputExchangeItem(int exchangeItemindex)
        {
            return (Oatc.OpenMI.Sdk.Backbone.InputExchangeItem)this._inputExchangeItems[exchangeItemindex];
        }
        public Oatc.OpenMI.Sdk.Backbone.OutputExchangeItem GetOutputExchangeItem(int exchangeItemindex)
        {
            return (Oatc.OpenMI.Sdk.Backbone.OutputExchangeItem)this._outputExchangeItems[exchangeItemindex];
        }
        public int GetOutputExchangeItemCount()
        {
            return this._outputExchangeItems.Count;
        }
        public int GetInputExchangeItemCount()
        {
            return this._inputExchangeItems.Count;
        }
        public void SetValues(string QuantityID, string ElementSetID, global::OpenMI.Standard.IValueSet value)
        {
            bool found = false;

            for (int i = 0; i < _daisyEngine.ScopeSize(); i++)
            {
                Scope scope = _daisyEngine.GetScope(i);

                if (!scope.HasString("column"))
                    continue;
                if (!scope.Writeable())
                    continue;

                if (scope.String("column") != ElementSetID)
                    continue;

                for (uint j = 0; j < scope.NumberSize(); j++)
                {
                    if (scope.NumberName(j) == QuantityID)
                    {
                        if (found)
                            throw new Exception("Duplicate QuantityID: '" + QuantityID + "' used as argument in Daisy SetValues method");
                        global::OpenMI.Standard.IScalarSet val = (global::OpenMI.Standard.IScalarSet)value;
                        if (scope.IsNumber(QuantityID))
                            scope.SetNumber(QuantityID, val.GetScalar(0));
                        found = true;
                    }
                }
            }
            if (!found)
                throw new Exception("No QuantityID: '" + QuantityID + "' used as argument in Daisy SetValues method");
        }
        public bool PerformTimeStep()
        {
            _daisyEngine.TickTime();
            DateTime time = _daisyEngine.GetTime();
            Console.Write("*** " + time.Year);
            Console.Write("-" + time.Month);
            Console.WriteLine("-" + time.Day);
            return true; // Hvis modellen skal reducere sit "timestep" return false
        }
        public void Dispose()
        {
            _daisyEngine.Dispose();
        }
        public void Finish()
        {
        }
    }

    public class DaisyOpenMIComponent : Oatc.OpenMI.Sdk.Wrapper.LinkableEngine
    {
        protected override void SetEngineApiAccess ()
        {
            // Create the DaisyWrapper and assigns it to the protected 
            // field variable _engineApiAccess:
            _engineApiAccess = new DaisyWrapper ();
        }
    } 
}
