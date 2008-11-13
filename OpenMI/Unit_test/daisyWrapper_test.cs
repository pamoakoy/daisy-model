using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using dk.ku.life.Daisy.OpenMI;

namespace Unit_test
{
   [TestFixture]
   public class daisyWrapper_test
    {
        static DaisyWrapper GetInitDaisy()
        {
            DaisyWrapper Daisy = new DaisyWrapper();
            System.Collections.Hashtable table = new System.Collections.Hashtable();
            table.Add("FilePath", "../../DaisyData/test_check.dai");
            Daisy.Initialize(table);
            return Daisy;
        }
        [Test]
        public void Initialize()
        {
            DaisyWrapper daisy = GetInitDaisy();
        }
        [Test]
        public void CountColumns()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(2, daisy.CountColumns());
        }
        [Test]
        public void IsRunning()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(true, daisy.IsRunning());
        }
        [Test]
        public void StartTime()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(new DateTime(1986, 12, 1, 1, 0, 0), daisy.StartTime);
        }
        [Test]
        public void EndTime()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(new DateTime(1988, 4, 1, 1, 0, 0), daisy.EndTime);
        }
        [Test]
        public void GetTime()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(new DateTime(1986, 12, 1, 1, 0, 0), daisy.GetTime());
            daisy.PerformTimeStep();
            Assert.AreEqual(new DateTime(1986, 12, 1, 1, 0, 0).AddHours(1), daisy.GetTime());
        }
        [Test]
        public void GetEndTime()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual(new DateTime(1988, 4, 1, 1, 0, 0), daisy.GetEndTime());
        }
        [Test]
        public void GetDescription()
        {
            DaisyWrapper daisy = GetInitDaisy();
            Assert.AreEqual("Simulation for use in tutorial.", daisy.GetDescription());
        }
        [Test]
        public void TimeHorizon()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            DateTime time = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.ModifiedJulian2Gregorian(Daisy.GetTimeHorizon().Start.ModifiedJulianDay);
            Assert.AreEqual(new DateTime(1986, 12, 1, 1, 0, 0), time);
        }
        [Test]
        public void GetInputTime()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Oatc.OpenMI.Sdk.Backbone.TimeStamp time = new Oatc.OpenMI.Sdk.Backbone.TimeStamp();
            time.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(new DateTime(1986, 12, 1, 1, 0, 0));
            Assert.AreEqual(time, Daisy.GetInputTime("crop_height", "elementset"));
        }
        [Test]
        public void GetCurrentTime()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Oatc.OpenMI.Sdk.Backbone.TimeStamp time = new Oatc.OpenMI.Sdk.Backbone.TimeStamp();
            time.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(new DateTime(1986, 12, 1, 1, 0, 0));
            Assert.AreEqual(time, Daisy.GetCurrentTime());
        }
        [Test]
        public void GetEarliestNeededTime()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Oatc.OpenMI.Sdk.Backbone.TimeStamp time = new Oatc.OpenMI.Sdk.Backbone.TimeStamp();
            time.ModifiedJulianDay = Oatc.OpenMI.Sdk.DevelopmentSupport.CalendarConverter.Gregorian2ModifiedJulian(new DateTime(1986, 12, 1, 1, 0, 0));
            Assert.AreEqual(time, Daisy.GetEarliestNeededTime());
        }
        [Test]
        public void GetModelID()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Assert.AreEqual("../../DaisyData/test_check.dai", Daisy.GetModelID());
        }
       [Test]
       public void PerformTimestep()
       {
           DaisyWrapper Daisy = GetInitDaisy();
           Assert.AreEqual(true, Daisy.PerformTimeStep());
       }
        [Test]
        public void GetDescriptions()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Assert.AreEqual("Simulation for use in tutorial.", Daisy.GetModelDescription());
            Assert.AreEqual("Daisy version 4.55", Daisy.GetComponentDescription());
            Assert.AreEqual("Simulation for use in tutorial.", Daisy.GetDescription());
        }
        [Test]
        public void GetMissingValueDefinition()
        {
            DaisyWrapper Daisy = GetInitDaisy();
            Assert.AreEqual(-999999.99, Daisy.GetMissingValueDefinition());
        }
       [Test]
       public void GetValues()
       {
           DaisyWrapper Daisy = GetInitDaisy();
           global::OpenMI.Standard.IValueSet value = Daisy.GetValues("height", "Gaaseroed");
           Oatc.OpenMI.Sdk.Backbone.ScalarSet test = (Oatc.OpenMI.Sdk.Backbone.ScalarSet)value;
           Assert.AreEqual(1, value.Count);
           Assert.AreEqual(Daisy.GetMissingValueDefinition(), test.data[0]);

           Daisy.PerformTimeStep();
           value = Daisy.GetValues("Water", "Andeby");
           Assert.AreEqual(1, value.Count);
           test = (Oatc.OpenMI.Sdk.Backbone.ScalarSet)value;
           Assert.Greater(test.data[0],400);
       }
       [Test]
       public void SetValues()
       {
           DaisyWrapper Daisy = GetInitDaisy();
           Oatc.OpenMI.Sdk.Backbone.ScalarSet val = new Oatc.OpenMI.Sdk.Backbone.ScalarSet();
           val.data = new double[1];
           val.data[0] = 100.100;
           Daisy.SetValues("GroundWaterTable", "Andeby", val);
       }
       [Test]
       public void GetInputExchangeItem()
       {
           DaisyWrapper Daisy = GetInitDaisy();
           int item = 0;
           Assert.AreEqual("GroundWaterTable", Daisy.GetInputExchangeItem(item).Quantity.ID);
           Assert.AreEqual("cm", Daisy.GetInputExchangeItem(item).Quantity.Unit.ID);
           Assert.AreEqual("Ground water table.", Daisy.GetInputExchangeItem(item).Quantity.Description);
           Assert.AreEqual(global::OpenMI.Standard.ElementType.XYPoint, Daisy.GetInputExchangeItem(item).ElementSet.ElementType);
           Assert.AreEqual(1, Daisy.GetInputExchangeItem(item).ElementSet.GetVertexCount(0));
           Assert.AreEqual(-10, Daisy.GetInputExchangeItem(item).ElementSet.GetXCoordinate(0, 0));
           Assert.AreEqual(100, Daisy.GetInputExchangeItem(item).ElementSet.GetYCoordinate(0, 0));
       }
       [Test]
       public void GetOutputExchangeItem()
       {
           DaisyWrapper Daisy = GetInitDaisy();
           Assert.AreEqual("Water", Daisy.GetOutputExchangeItem(0).Quantity.ID);
           Assert.AreEqual("mm", Daisy.GetOutputExchangeItem(0).Quantity.Unit.ID);
           Assert.AreEqual("DS", Daisy.GetOutputExchangeItem(1).Quantity.ID);
           Assert.AreEqual("<none>", Daisy.GetOutputExchangeItem(1).Quantity.Unit.ID);
           Assert.AreEqual("Crop AI", Daisy.GetOutputExchangeItem(4).Quantity.ID);
           Assert.AreEqual("m^2/m^2", Daisy.GetOutputExchangeItem(4).Quantity.Unit.ID);
           Assert.AreEqual(-10, Daisy.GetOutputExchangeItem(0).ElementSet.GetXCoordinate(0, 0));
           Assert.AreEqual(100, Daisy.GetOutputExchangeItem(0).ElementSet.GetYCoordinate(0, 0));
           Assert.AreEqual(-10, Daisy.GetOutputExchangeItem(1).ElementSet.GetXCoordinate(0, 0));
           Assert.AreEqual(100, Daisy.GetOutputExchangeItem(1).ElementSet.GetYCoordinate(0, 0));
           Assert.AreEqual(-10, Daisy.GetOutputExchangeItem(4).ElementSet.GetXCoordinate(0, 0));
           Assert.AreEqual(100, Daisy.GetOutputExchangeItem(4).ElementSet.GetYCoordinate(0, 0));

       }
    }
}