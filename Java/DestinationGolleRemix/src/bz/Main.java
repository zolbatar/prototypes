package bz;

import bz.ecs.Components;
import bz.ecs.Controllers;
import bz.ecs.Vector;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import org.magnos.entity.Entity;
import org.magnos.entity.Ents;
import org.magnos.entity.Template;
import org.magnos.entity.util.ComponentSet;
import org.magnos.entity.util.ControllerSet;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        System.out.println(Screen.getPrimary().getDpi());
        Parent root = FXMLLoader.load(getClass().getResource("panels/Main.fxml"));
        primaryStage.setTitle("Destination Golle: ReMiX");
        primaryStage.setScene(new Scene(root, 1366, 768));
        primaryStage.show();

        Template SPRITE = Ents.newTemplate("sprite", new ComponentSet(Components.POSITION, Components.VELOCITY), new ControllerSet(Controllers.PHYSICS));

        Entity e = new Entity(SPRITE);
        e.get(Components.POSITION).set(1.0f, 3.0f);
        e.get(Components.VELOCITY).set(0.0f, -6.0f);
//        e.update(0.5f);

        e.put(Components.ACCELERATION, new Vector(0.0f, -10.0f));
        e.add(Controllers.PHYSICS_ACCELERATION); // overwrite existing PHYSICS controller with this alternative

        assert e.has(Controllers.PHYSICS);
        System.out.println(e);

        e.update(0.5f);
        System.out.println(e);

    }


    public static void main(String[] args) {
        launch(args);
    }
}
