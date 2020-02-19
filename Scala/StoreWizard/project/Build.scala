import sbt._
import Keys._
import PlayProject._

object ApplicationBuild extends Build {

    val appName         = "StoreWizard"
    val appVersion      = "1.0-SNAPSHOT"

    val appDependencies = Seq(
      "com.novus" %% "salat" % "0.0.8"
    )

    val main = PlayProject(appName, appVersion, appDependencies, mainLang = SCALA).settings(
      // Add your own project settings here      
    )

}
