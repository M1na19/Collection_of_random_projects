using System.Text.Json.Nodes;
using System.Diagnostics;
using System.Runtime.InteropServices.Marshalling;
using System.Data;
public sealed class Enviroment{
    public int NrRows;
    public int NrSeats;
    public int MaxGroups;

    public int MaxSwitch;

    public int ChanceGroupAdd;
    public int ChanceGroupRemove;
    public int ChanceSwitch;
    public float WalkTimeMax;
    public float WalkTimeMin;
    public float WaitTimeMax;
    public float WaitTimeMin;
    public int NrTests; 

    public int NrGenerations;
    public int NrPopulation;
    public int NrElite;

    public int AlikeThreshHold;
    public Enviroment(){}//manual
    public Enviroment(string file){
        string content=string.Join("",File.ReadAllText(file));
        JsonNode? json=JsonObject.Parse(content);

        #pragma warning disable
        Debug.Assert(json!=null);
        NrRows=(int)json["AirplaneConfig"]["NumberRows"];
        NrSeats=(int)json["AirplaneConfig"]["NumberSeats"];
        MaxGroups=(int)json["PassangerConfig"]["MaxGroups"];
        MaxSwitch=(int)json["MutationConfig"]["MaxSwitch"];
        ChanceGroupAdd=(int)json["MutationConfig"]["ChanceGroupAdd"];
        ChanceGroupRemove=(int)json["MutationConfig"]["ChanceGroupRemove"];
        ChanceSwitch=(int)json["MutationConfig"]["ChanceSwitch"];
        WaitTimeMax=(int)json["SimulationConfig"]["WaitTimeMax"];
        WaitTimeMin=(int)json["SimulationConfig"]["WaitTimeMin"];
        WalkTimeMax=(int)json["SimulationConfig"]["WalkTimeMax"];
        WalkTimeMin=(int)json["SimulationConfig"]["WalkTimeMin"];
        AlikeThreshHold=(int)json["MatingConfig"]["AlikeThreshHold"];
        NrGenerations=(int)json["SimulationConfig"]["NrGenerations"];
        NrPopulation=(int)json["SimulationConfig"]["NrPopulation"];
        NrElite=(int)json["SimulationConfig"]["NrElite"];
        NrTests=(int)json["SimulationConfig"]["NumberTestsForFitness"];

        #pragma warning restore
    }   
}
class Airplane{
    public int NrRows{ get;set;}
    public int NrSeats{ get;set;} 

    public int  NrGroups{get;set;}
    float fitness;
    public class Passanger{
        public int Row{ get;}
        public char Seat{ get;}

        public Passanger(int row,char seat){
            this.Row=row;
            this.Seat=seat;
        }
        public string AsKey(){
            return Row.ToString()+Seat.ToString();
        }
        public static Passanger FromKey(string key){
            return new Passanger(Convert.ToInt32(key.Substring(0,key.Length-1)),key[key.Length-1]);
        }
    }

    Dictionary<string,int> config=new Dictionary<string,int>();

    public void AddPassanger(Passanger pass,int group_id){
        Debug.Assert(group_id<=NrGroups);
        config[pass.AsKey()]=group_id;
    }
    public void RemovePassanger(Passanger pass){
        config.Remove(pass.AsKey());
    }
    public int GetPassangerGroup(Passanger pass){
        return config[pass.AsKey()];
    }
    public void CreateGroup(){NrGroups++;}

    public List<Passanger> RemoveRandomGroup(){
        int randomEliminated=Random.Shared.Next(1,NrGroups+1);

        List<Passanger> eliminated=new List<Passanger>();
        foreach(var seat in config){
            if(seat.Value==randomEliminated){
                eliminated.Add(Passanger.FromKey(seat.Key));
            }
        }
        foreach(var pass in eliminated){
            config.Remove(pass.AsKey());
        }
        foreach(var seat in config){
            if(seat.Value>randomEliminated){
                config[seat.Key]--;
            }
        }
        NrGroups--;
        return eliminated;
    }
    public Dictionary<string,int> GetPassangerConfig(){
        return config;
    }
    public float GetFitness(){
        return fitness;
    }
    public void Evaluate(Fitness fn){
        fitness=fn.Value(this);
    }
    public Airplane(Enviroment env){
        NrRows=env.NrRows;
        NrSeats=env.NrSeats;
        NrGroups=Random.Shared.Next(1,env.MaxGroups+1);

        for(int row=1;row<=NrRows;row++){
            for(char seat='A';seat<'A'+NrSeats;seat++){
                Passanger pass=new Passanger(row,seat);
                int randGroup=Random.Shared.Next(1,NrGroups+1);
                config.Add(pass.AsKey(),randGroup);
            }
        }
    }
    public Airplane(){}

    public Airplane Clone(){
        Airplane clone=new Airplane();

        clone.NrRows=NrRows;
        clone.NrSeats=NrSeats;
        clone.NrGroups=NrGroups;
        clone.fitness=fitness;
        clone.config=new Dictionary<string, int>(config);
        return clone;
    }
    public override string ToString()
    {
        string output=NrGroups.ToString()+'\n';
        output+="  ";
        for(char seat='A';seat<'A'+NrSeats;seat++){
            if(seat=='A'+NrSeats/2-1)output+=seat+"     ";
            else output+=seat+" ";
        }output+=" \n";
        for(int row=1;row<=NrRows;row++){
            output+="| ";
            for(char seat='A';seat<'A'+NrSeats;seat++){
                Passanger pass=new Passanger(row,seat);
                if(seat=='A'+NrSeats/2-1)output+=config[pass.AsKey()].ToString()+" | | ";
                else output+=config[pass.AsKey()].ToString()+" ";
            }output+="| "+row.ToString()+"\n";
        }
        return output;
    }
}